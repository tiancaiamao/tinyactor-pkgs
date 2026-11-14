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
OUT := lib/markdown.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): markdown_glue.c src/md4c/md4c.c src/md4c/md4c.h $(TINYACTOR)/ta.h | lib
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) -I$(TINYACTOR) -Isrc -o $@ markdown_glue.c src/md4c/md4c.c

lib:
	mkdir -p lib

# 运行期按 cwd 相对路径找 lib/markdown.$(EXT)，所以测试在包目录里跑。
test: all
	printf 'tinyactor\t%s\ntinyactor-pkgs\t..\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	$(TINYACTOR)/tinyactor run smoke.ta
	$(TINYACTOR)/tinyactor run test-markdown.ta

clean:
	rm -rf lib vendor tinyactor.deps tinyactor.lock