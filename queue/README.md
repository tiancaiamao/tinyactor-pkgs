# queue

Status: implemented — pure TinyActor, no C dependencies.

FIFO persistent queue backed by two lists. Empty `pop` returns `Empty`; `peek` returns `None`.
`make test TINYACTOR=/path/to/core-copy` runs the behavior test. No C build is needed.

API (all signatures explicit in `queue.ta`): `new`, `push`, `pop`, `peek`, `size`, `is_empty`.