# tinyactor-pkgs

Third-party packages for [tinyactor](https://github.com/tiancaiamao/tinyactor).
Core stdlib is capped at Janet scale (`vm → bootstrap → lib → third party`);
everything beyond that boundary lives here. The package mechanism — C source plus
its `external fn` declaration in the package's own tree, imported by that tree
name — is [docs/c-module.md §9](https://github.com/tiancaiamao/tinyactor/blob/main/docs/c-module.md)
in the core repo.

## Packages

| Package | Status | Tier |
|---|---|---|
| `_template/` | reference package — minimal C module + TA glue + self-contained smoke test | — |
| `sqlite` | implemented — system SQLite wrapper, CRUD smoke/tests | T1 |
| `markdown` | implemented — md4c 0.5.2 vendored dynamic module; returns `html.Node` | T1 |
| `yaml` | implemented — libyaml 0.2.5 vendored dynamic module | T1 |
| `queue` / `deque` / `priority_queue` | implemented — pure TA FIFO/deque/stable priority queue | T1 |
| `sdl` | implemented — SDL2 wrapper, headless smoke/tests | T1 |
| `unicode` | implemented — pure-TA UTF-8 encode/decode, dual-view metrics, iteration | T2 |
| `regexp` | implemented — pure-TA regexp parser + Thompson NFA simulator | T2 |
| `decimal` / `rational` | implemented — exact base-10 decimal & reduced rational on shared digit-string bigint base | T2 |
| `num_internal` | implemented — shared unsigned digit-string arithmetic, internal base for `decimal` / `rational` | T2 |

Every package is on the single-root import syntax: core modules come in as
`import "tinyactor:lib/<mod>"`, sibling packages as
`import "tinyactor-pkgs:<pkg>/<pkg>"`. Each package is also its own consumer —
`make test` writes a `tinyactor.deps` with two trees (this repo + the core
repo, `TINYACTOR ?= ../../tinyactor`), runs `tinyactor vendor`, then runs the
package test from the package directory (C packages build `lib/<mod>.<ext>`
there, which is where the runtime looks for it). No copying into a core
checkout, no `/tmp` core copies.

Types and constructors are module members exactly like functions, so a package
writes them with the import reference: `result.Result(int, string)`,
`result.Ok(v)`, `option.Some(x)`. Bare names are only the package's *own*
declarations and the language primitives (`List`, `Int`, …). No prelude.
