# regexp

Status: implemented v1 pure-TA regular-expression engine.

## API

- `compile(pattern: string) -> CompileResult`, where `Compiled(regex)` or `BadPattern(reason)`
- `matches(regex: Regex, text: string) -> bool`
- `find(pattern: string, text: string) -> string`
- `find_all(pattern: string, text: string) -> list(string)`
- `replace(pattern: string, text: string, replacement: string) -> string`

`find` returns the leftmost longest match, or `""` when none is found. `find_all` returns non-overlapping leftmost-longest matches. Empty matches advance one character; the terminal empty match is included once. `replace` replaces each such match. Invalid patterns produce `BadPattern` from `compile`; convenience functions return empty list/string or original text on invalid patterns.

## v1 syntax

| Syntax | Support |
|---|---|
| Literals | Yes |
| `.` | Yes; matches any character |
| Character classes `[a-z]`, `[^a-z]` | Yes |
| `^` / `$` | Yes; beginning/end of input |
| `*` / `+` / `?` | Yes; greedy longest match |
| Groups `(…)` | Yes; non-capturing |
| Alternation `|` | Yes |

Named captures, capture extraction, lookaround, backreferences, escapes, and lazy quantifiers are not supported.

## Engine

Thompson NFA simulation with epsilon-closure visited sets. Unlike recursive backtracking, nested repetition such as `((a*)*)b` stays bounded by input length times NFA size rather than expanding into exponentially many paths.

Run isolated-core tests with `make test TINYACTOR=/path/to/tinyactor`.
---

Implementation note: syntax rejection currently covers malformed groups/classes and misplaced operators. The package is intentionally a small regex subset, not a PCRE-compatible engine.

---

## Test evidence

Command: `make -C regexp test TINYACTOR=/Users/genius/project/tinyactor`

The Makefile copies the core tree to a fresh `/tmp/ta-regexp.*`, installs only `regexp.ta` into that copy, and runs `test-regexp.ta` with `--no-cache`. Output:

```text
PASS invalid pattern
PASS invalid quantifier
PASS unclosed group
true
aa
PASS regexp tests
```

Exit status: 0. Tests cover literals, dot, positive/negative character classes, anchors, all three quantifiers, grouping, alternation, empty input, find, empty-match `find_all` progression including terminal boundary, replace, rejection of invalid patterns, and `((a*)*)b` against 30 `a` characters.

No core repository files were modified. Remaining limitation: `find` uses the empty string both for “no match” and a successful empty match; use `matches`/`find_all` where that distinction matters.
```