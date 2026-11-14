# SDL2 package

Status: implemented — small SDL2 lifecycle/window/event-pump wrapper (T1).

`Window` is a mutable opaque handle backed by `SDL_Window *`; SDL operations act
on that same handle. Call `destroy_window` explicitly. `quit` also reclaims any
still-open windows. Actor exit without `quit` does not reclaim them (v1 lifecycle
convention).

Tests use `SDL_VIDEODRIVER=dummy`; they exercise SDL initialization, a hidden
window, event polling, delay, and teardown without requiring a display server or
real rendering.

Build with `make` (output `lib/sdl.dylib`); `sdl2-config --cflags --libs` supplies
platform SDL2 paths and link flags. `make test TINYACTOR=<core repo>` vendors the
package as its own dependency and runs smoke plus the suite headless
(`SDL_VIDEODRIVER=dummy`) from the package directory.