# deque

Status: implemented — pure TinyActor, no C dependencies.

Immutable deque backed by a list in front-to-back order; front operations are O(1), back operations O(n). Empty pops return `Empty`; peeks return `None`.
`make test TINYACTOR=/path/to/core-copy` runs the behavior test. No C build is needed.

API (all signatures explicit in `deque.ta`): `new`, `push_front`, `push_back`, `pop_front`, `pop_back`, `peek_front`, `peek_back`, `size`, `is_empty`.