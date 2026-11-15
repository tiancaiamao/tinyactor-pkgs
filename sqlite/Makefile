CC ?= cc
TINYACTOR ?= ../../tinyactor
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
EXT := dylib
SHARED_FLAGS := -undefined dynamic_lookup
SQLITE_PREFIX ?= $(shell brew --prefix sqlite3 2>/dev/null)
SQLITE_CFLAGS := $(if $(SQLITE_PREFIX),-I$(SQLITE_PREFIX)/include,)
SQLITE_LIBS := $(if $(SQLITE_PREFIX),-L$(SQLITE_PREFIX)/lib,)
else
EXT := so
SHARED_FLAGS :=
SQLITE_CFLAGS :=
SQLITE_LIBS :=
endif
OUT := lib/sqlite.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): sqlite_glue.c $(TINYACTOR)/ta.h | lib
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) $(SQLITE_CFLAGS) -I$(TINYACTOR) -o $@ sqlite_glue.c $(SQLITE_LIBS) -lsqlite3

lib:
	mkdir -p lib

# 运行期按 cwd 相对路径找 lib/sqlite.$(EXT)，所以测试在包目录里跑。
test: all
	printf 'tinyactor\t%s\ntinyactor-pkgs\t..\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	$(TINYACTOR)/tinyactor run smoke.ta
	$(TINYACTOR)/tinyactor run test-sqlite.ta

clean:
	rm -rf lib vendor tinyactor.deps tinyactor.lock