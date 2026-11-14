# queue

Status: implemented — pure TinyActor, no C dependencies.

FIFO persistent queue backed by two lists. Empty `pop` returns `Empty`; `peek` returns `None`.
`make test TINYACTOR=<core repo>` vendors the package as its own dependency (`tinyactor.deps` → `vendor/`) and runs the behavior test. No C build is needed.

API (all signatures explicit in `queue.ta`): `new`, `push`, `pop`, `peek`, `size`, `is_empty`.