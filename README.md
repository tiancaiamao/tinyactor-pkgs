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
| `markdown` (md4c) | planned — extraction from core branch `std-batch6-docs` | T1 |
| `yaml` (libyaml) | planned — same | T1 |
| `queue` / `deque` / `priority_queue` | planned (pure ta) | T1 |
| `sdl` | implemented — SDL2 wrapper, headless smoke/tests | T1 |