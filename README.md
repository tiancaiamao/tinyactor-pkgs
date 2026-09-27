# tinyactor-pkgs

Third-party packages for [tinyactor](https://github.com/tiancaiamao/tinyactor).
Core stdlib is capped at Janet scale (`vm → bootstrap → lib → third party`);
everything beyond that boundary lives here. See
[docs/packages.md](https://github.com/tiancaiamao/tinyactor/blob/main/docs/packages.md)
in the core repo for the package mechanism (v1: build a package, copy its
artifacts into your project's `lib/`).

## Packages

| Package | Status | Tier |
|---|---|---|
| `_template/` | minimal C-module template (smoke test with four-state verdict) | — |
| `sqlite` | implemented — system SQLite wrapper, CRUD smoke/tests | T1 |
| `markdown` | implemented — md4c 0.5.2 vendored dynamic module; returns `html.Node` | T1 |
| `yaml` | implemented — libyaml 0.2.5 vendored dynamic module | T1 |
| `queue` / `deque` / `priority_queue` | implemented — pure TA FIFO/deque/stable priority queue | T1 |
| `sdl` | implemented — SDL2 wrapper, headless smoke/tests | T1 |
| `unicode` | implemented — pure-TA UTF-8 encode/decode, dual-view metrics, iteration | T2 |
| `regexp` | implemented — pure-TA regexp parser + Thompson NFA simulator | T2 |
| `decimal` / `rational` | implemented — exact base-10 decimal & reduced rational on shared digit-string bigint base | T2 |
| `num_internal` | implemented — shared unsigned digit-string arithmetic, internal base for `decimal` / `rational` | T2 |
