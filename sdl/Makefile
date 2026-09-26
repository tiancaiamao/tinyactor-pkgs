CC ?= cc
TINYACTOR ?= ../tinyactor
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
EXT := dylib
SHARED_FLAGS := -undefined dynamic_lookup
else
EXT := so
SHARED_FLAGS :=
endif
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS := $(shell sdl2-config --libs)
OUT := sdl.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): sdl_glue.c $(TINYACTOR)/ta.h
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) $(SDL_CFLAGS) -I$(TINYACTOR) -o $@ $< $(SDL_LIBS)

clean:
	rm -f $(OUT)

test: all
	@set -e; tmp=$$(mktemp -d /tmp/tinyactor-sdl.XXXXXX); \
	trap 'rm -rf "$$tmp"' EXIT; \
	cp -R $(TINYACTOR) "$$tmp/tinyactor"; \
	cp sdl.ta $(OUT) "$$tmp/tinyactor/lib/"; \
	cd "$$tmp/tinyactor"; \
	SDL_VIDEODRIVER=dummy ./tinyactor run --no-cache $(CURDIR)/smoke.ta; \
	SDL_VIDEODRIVER=dummy ./tinyactor run --no-cache $(CURDIR)/test-sdl.ta