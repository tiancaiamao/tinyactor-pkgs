# yaml

Status: implemented — vendored libyaml 0.2.5 parser, built as a dynamic module.

The parse-only API is `yaml.try_parse` / `yaml.parse`; see `yaml.ta` for
complete signatures. No system library dependency is required.

Build with `make` (output `lib/yaml.dylib`); `make test TINYACTOR=<core repo>`
vendors the package as its own dependency (`tinyactor.deps` → `vendor/`) and runs
smoke plus the full package suite from the package directory.

`src/yaml/README` records vendored provenance, source status, and license;
`src/yaml/LICENSE` accompanies the upstream sources.

