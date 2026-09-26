#include "ta.h"
#include <SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char sdl_error[512];
typedef struct WindowNode {
    SDL_Window *window;
    struct WindowNode *next;
} WindowNode;
static WindowNode *windows;


static int window_register(SDL_Window *window) {
    WindowNode *node = malloc(sizeof(*node));
    if (!node) return -1;
    node->window = window;
    node->next = windows;
    windows = node;
    return 0;
}


static Val raw_init(VM *vm, Val *a, int n) {
    (void)vm; (void)a; (void)n;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        snprintf(sdl_error, sizeof(sdl_error), "%s", SDL_GetError());
        return val_int(-1);
    }
    sdl_error[0] = '\0';
    return val_int(0);
}
static Val raw_error(VM *vm, Val *a, int n) {
    (void)vm; (void)a; (void)n;
    return val_string(tls_current_proc, sdl_error, (int)strlen(sdl_error));
}
static Val raw_create_window(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    if (!val_is_string(a[0])) return val_int(-1);
    HeapString *title = val_get_string(a[0]);
    SDL_Window *window = SDL_CreateWindow(title->data, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, (int)val_get_int(a[1]), (int)val_get_int(a[2]),
        SDL_WINDOW_HIDDEN);
        if (!window) {
        snprintf(sdl_error, sizeof(sdl_error), "%s", SDL_GetError());
        return val_int(-1);
    }
    if (window_register(window) != 0) {
        SDL_DestroyWindow(window);
        snprintf(sdl_error, sizeof(sdl_error), "out of memory");
        return val_int(-1);
    }
    return val_int((int64_t)(uintptr_t)window);
}
static Val raw_destroy_window(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    SDL_Window *window = (SDL_Window *)(uintptr_t)val_get_int(a[0]);
    WindowNode **link = &windows;
    while (*link && (*link)->window != window) link = &(*link)->next;
    if (!*link) return val_int(-1);
    WindowNode *node = *link;
    *link = node->next;
    SDL_DestroyWindow(window);
    free(node);
    return val_int(0);
}

static Val raw_poll_event(VM *vm, Val *a, int n) {
    (void)vm; (void)a; (void)n;
    SDL_Event event;
    return val_int(SDL_PollEvent(&event) ? (int64_t)event.type : 0);
}
static Val raw_delay(VM *vm, Val *a, int n) {
    (void)vm; (void)n;
    int64_t ms = val_get_int(a[0]);
    if (ms < 0 || ms > UINT32_MAX) return val_int(-1);
    SDL_Delay((Uint32)ms);
    return val_int(0);
}
static Val raw_quit(VM *vm, Val *a, int n) {
    (void)vm; (void)a; (void)n;
    while (windows) {
        WindowNode *next = windows->next;
        SDL_DestroyWindow(windows->window);
        free(windows);
        windows = next;
    }
    SDL_Quit();
    return val_int(0);
}

static TaFunc funcs[] = {
    {"raw_init", raw_init, 0}, {"raw_error", raw_error, 0},
    {"raw_create_window", raw_create_window, 3},
    {"raw_destroy_window", raw_destroy_window, 1},
    {"raw_poll_event", raw_poll_event, 0}, {"raw_delay", raw_delay, 1},
    {"raw_quit", raw_quit, 0}, {NULL, NULL, 0}
};
void vm_load_self(VM *vm) { vm_register_module(vm, "sdl", funcs, 7); }