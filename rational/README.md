# rational

Status: implemented — pure TinyActor; arbitrary-precision numerators/denominators via the shared `num_internal` digit-string base (copied into the core `lib/` by the Makefile). No floating point, no native-int magnitude limits.

API: `make(num : string, den : string) -> Result(Rational, string)`, `add/sub/mul(Rational, Rational) -> Rational`, `div(Rational, Rational) -> Result(Rational, string)`, `compare(Rational, Rational) -> int`, `to_string(Rational) -> string`.

Semantic commitments:
- Representation is a sign tag (+1/-1) plus nonnegative digit-string numerator and positive digit-string denominator, always kept reduced (gcd == 1). Zero is always `1/1` with a `+` tag; text form is `numerator/denominator`.
- `make` rejects malformed integer strings (`Err`) and zero denominators (`Err`); a negative denominator's sign is folded into the tag, so the stored denominator is always positive (`2/-4` == `-1/2`).
- `div` by a zero rational returns `Err("division by zero")` (never panics).
- `add/sub/mul` re-reduce via gcd; `compare` cross-multiplies, so no magnitude division happens outside reduction. Magnitudes use decimal digit strings, so arithmetic is not limited to native int width (see the 30-digit test).

Run `make test TINYACTOR=/tmp/core-copy` (stages `../num_internal/num_internal.ta` itself).