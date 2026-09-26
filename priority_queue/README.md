# priority_queue

Status: implemented — pure TinyActor, no C dependencies.

Persistent sorted-list priority queue. Push is O(n); pop is O(1). Lower comparator result means earlier removal; ties retain FIFO insertion order. Empty `pop` returns `Empty`; `peek` returns `None`.
`make test TINYACTOR=/path/to/core-copy` runs the behavior test. No C build is needed.

`new(compare)` accepts a curried comparator `compare : t -> t -> int`; `compare(a)(b) < 0` means `a` is removed first. `int_new()` provides ascending integer order. The comparator is retained by the queue.