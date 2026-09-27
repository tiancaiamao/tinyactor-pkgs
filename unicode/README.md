# unicode

Status: implemented v1 pure-TA UTF-8 semantics for TinyActor strings.

Zero C: everything is TA on top of the builtin byte-oriented `str` module
(`str.char_at` / `str.chr` / `str.substr` / `str.concat`). This module is
what the core `lib/str.ta` header comment defers to: core `str.length`
counts bytes and `str.upper`/`str.lower`/pad are ASCII-only; `unicode`
supplies the UTF-8 view.

## API

```ta
pub type Decode { Decoded(cp, size); Invalid }
pub type Step { Step(cp, start, size) }

pub fn encode(cp : int) -> string
pub fn decode_at(s : string, i : int) -> Decode
pub fn is_valid(s : string) -> bool
pub fn byte_length(s : string) -> int
pub fn codepoint_length(s : string) -> int
pub fn codepoint_at(s : string, k : int) -> int
pub fn steps(s : string) -> list(Step)
pub fn is_ascii(s : string) -> bool
```

- `encode`: codepoint (0..U+10FFFF, surrogates U+D800..U+DFFF excluded)
  to UTF-8 bytes, full 1-4 byte path. Invalid codepoint (negative,
  surrogate, beyond U+10FFFF) returns `""` — unambiguous, because U+0000
  encodes to the 1-byte `chr(0)`, never `""`.
- `decode_at`: strict RFC 3629 decode at a byte index. `Invalid` on:
  truncated sequences, stray continuation bytes, overlong encodings
  (C0/C1 leads, E0 + <A0, F0 + <90), surrogates (ED + A0..BF), values
  beyond U+10FFFF (F4 + >=90, F5..FF leads), out-of-range index. A bad
  byte poisons its whole candidate sequence; no prefix is salvaged.
- `is_valid`: strict whole-string check (`""` is valid).
- `byte_length` / `codepoint_length`: the dual view. Invalid bytes count
  one codepoint each (replacement-style; see below).
- `codepoint_at`: k-th codepoint by codepoint index; `-1` when out of
  range or sitting on an invalid byte (matches `str.char_at`'s `-1`
  out-of-range convention).
- `steps`: iteration — one `Step(cp, start, size)` per codepoint with its
  byte span. Invalid bytes yield `Step(-1, i, 1)`: the `-1` sentinel
  distinguishes invalid data from an actual U+FFFD in the input (Go's
  `utf8.RuneError` model, with a sentinel instead of U+FFFD).
- `is_ascii`: every byte < 0x80 (`""` is ASCII).

## v1 not-doing list (explicit)

- **Case mapping beyond ASCII** (`str.upper`/`str.lower` for non-ASCII):
  not done. A correct table is thousands of entries (plus special
  casing like İ/ı, ß, Greek final sigma); v1 has no mechanism to
  hand-verify tables that large, so shipping a partial one would be
  dishonest. Callers needing non-ASCII case folding should bring data.
- **General category tables** (whitespace beyond ASCII, fullwidth/
  halfwidth, digits, letters, ...): not done, same table-verification
  reasoning. The only classification shipped is `is_ascii`, which is
  one comparison, not a table.
- **Normalization** (NFC/NFD), **grapheme clusters**: not done.
- **`U+FFFD` substitution on decode**: rejected on purpose — `-1`
  keeps invalid data distinguishable from real U+FFFD input.

None of the above is implied by the v1 API shape; widening later is
additive.

## Design note

The decoder is the range-table scheme (Höhrmann-style): each lead byte
class constrains the *second* byte's range (E0→A0..BF, ED→80..9F,
F0→90..BF, F4→80..8F, otherwise 80..BF), and bytes three and four are
always 80..BF. That single mechanism rejects overlongs, surrogates,
out-of-range values, truncation, and stray continuations with no
post-hoc value checks. The whole module is ~40 lines of logic.

## Compiler rejections this package relies on (reproduced)

The test file builds byte literals with `str.chr` + `str.concat` because:

1. **No hex int literals.** `unicode.encode(0xF0)` fails to compile:

   ```text
   typecheck: 2 type error(s) found
     [E0002] in function 'main' (line 2): undefined variable 'xF0'
     [E0001] in function 'main' (line 2): arg 2 of unicode.encode: cannot unify string with 'a -> 'b
   compile aborted: 2 type error(s)
   error: build failed - no output produced
   ```

2. **No `\xNN` string escapes** (worse: silently kept literal).
   `let s = "\xC3\xA9"; print(str.length(s))` compiles and prints `8`
   with `str.char_at(s, 0) == 92` (backslash) — the bytes are the eight
   characters `\xC3\xA9`, not two bytes. No error is raised.

(Also known and dodged: `str.concat` takes exactly 2 arguments; chains
are nested, never 3-arg.)

## Test evidence

Command: `make test TINYACTOR=/path/to/tinyactor` (the Makefile copies
the core tree into a fresh `/tmp/ta-unicode.*`, installs only
`unicode.ta` there, runs `test-unicode.ta` with `--no-cache`).

Output: `PASS unicode tests`, exit 0. Coverage: all four encode/decode
length classes at boundary codepoints (U+0000, U+007F, U+0080, U+07FF,
U+0800, U+4E2D 中, U+20AC €, U+FFFF, U+10000, U+1F600, U+20000, U+10FFFF);
encode rejection of negatives/surrogates/U+110000; round trips for every
length class; 15 invalid-sequence decode negatives (overlong ×3,
surrogate ×2, truncated ×3, bad continuation, stray continuation ×2,
beyond-max, F5 lead, FF lead, out-of-range index); whole-string
validity; dual-view metrics including the invalid-byte counting rule;
codepoint-indexed access; step iteration spans including invalid bytes;
`is_ascii`.

Red-injection self-checks (each reverts to green afterwards):
expected value tampered (U+4E2D last byte 173→172) → `FAIL encode
U+4E2D`, exit 1; decoder surrogate range relaxed (`ED` hi bound 159→191)
→ caught by `surrogate U+D800 ED A0 80`; overlong guard relaxed
(`b < 194` → `b < 192`) → caught by `overlong 2-byte C0 AF`.

No core repository files were modified.