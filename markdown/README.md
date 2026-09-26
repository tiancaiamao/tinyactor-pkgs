# markdown

Status: implemented — vendored md4c 0.5.2, built as a dynamic module.

`markdown.parse(text : string) -> Result(List(html.Node), string)` parses
Markdown into the core `html` Node ADT. Render the result with
`html.render_list`. No system library dependency is required.

Build with `make`; `make test TINYACTOR=/path/to/tinyactor` installs into
that core checkout and runs smoke plus the full package suite.

Vendored source: `src/md4c/README` records upstream provenance and confirms
zero local source changes.
