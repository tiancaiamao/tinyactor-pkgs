CC ?= cc
TINYACTOR ?= ../../tinyactor
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
OUT := lib/sdl.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): sdl_glue.c $(TINYACTOR)/ta.h | lib
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) $(SDL_CFLAGS) -I$(TINYACTOR) -o $@ sdl_glue.c $(SDL_LIBS)

lib:
	mkdir -p lib

# 运行期按 cwd 相对路径找 lib/sdl.$(EXT)，所以测试在包目录里跑；无显示器用 dummy 驱动。
test: all
	printf 'tinyactor\t%s\ntinyactor-pkgs\t..\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	SDL_VIDEODRIVER=dummy $(TINYACTOR)/tinyactor run smoke.ta
	SDL_VIDEODRIVER=dummy $(TINYACTOR)/tinyactor run test-sdl.ta

clean:
	rm -rf lib vendor tinyactor.deps tinyactor.lock