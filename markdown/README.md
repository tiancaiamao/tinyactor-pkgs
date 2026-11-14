# markdown

Status: implemented — vendored md4c 0.5.2, built as a dynamic module.

`markdown.parse(text : string) -> Result(List(html.Node), string)` parses
Markdown into the core `html` Node ADT. Render the result with
`html.render_list`. No system library dependency is required.

Build with `make` (output `lib/markdown.dylib`); `make test TINYACTOR=<core repo>`
vendors the package as its own dependency (`tinyactor.deps` → `vendor/`) and runs
smoke plus the full package suite from the package directory.

Vendored source: `src/md4c/README` records upstream provenance and confirms
zero local source changes.
