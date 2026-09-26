# yaml

Status: implemented — vendored libyaml 0.2.5 parser, built as a dynamic module.

The parse-only API is `yaml.try_parse` / `yaml.parse`; see `yaml.ta` for
complete signatures. No system library dependency is required.

Build with `make`; `make test TINYACTOR=/path/to/tinyactor` installs into
that core checkout and runs smoke plus the full package suite.

`src/yaml/README` records vendored provenance, source status, and license;
`src/yaml/LICENSE` accompanies the upstream sources.

