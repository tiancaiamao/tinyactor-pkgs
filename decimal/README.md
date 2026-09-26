# decimal

Status: implemented — pure TinyActor; no floating-point representation or dependencies. Magnitudes are decimal digit strings from the shared `num_internal` base (copied into the core `lib/` by the Makefile), so arithmetic is not limited to native int width.

API: `parse(string) -> Result(Decimal, string)`, `from_int(int) -> Decimal`, `add/sub/mul(Decimal, Decimal) -> Decimal`, `div(Decimal, Decimal) -> Result(Decimal, string)`, `compare(Decimal, Decimal) -> int`, `to_string(Decimal) -> string`.

Ordinary decimal notation only (no exponent). Addition, subtraction, multiplication and comparison are exact. Division keeps 18 fractional decimal places and truncates toward zero; division by zero returns `Err`. Coefficients use decimal digit strings, so arithmetic is not limited to native int width. Run `make test TINYACTOR=/tmp/core-copy`.

`to_string` trims trailing fractional zeros (`0.50` → `0.5`, `1.000` → `1`), never leaves a bare trailing dot for integer values, and suppresses negative zero (`-0.0` prints `0`).