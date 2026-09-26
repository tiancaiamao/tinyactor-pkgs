CC ?= cc
TINYACTOR ?= ../tinyactor
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
OUT := sqlite.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): sqlite_glue.c $(TINYACTOR)/ta.h
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) $(SQLITE_CFLAGS) -I$(TINYACTOR) -o $@ $< $(SQLITE_LIBS) -lsqlite3

clean:
	rm -f $(OUT)

test: all
	cp sqlite.ta $(TINYACTOR)/lib/sqlite.ta
	cp $(OUT) $(TINYACTOR)/lib/$(OUT)
		cd $(TINYACTOR) && ./tinyactor run --no-cache $(CURDIR)/smoke.ta && ./tinyactor run --no-cache $(CURDIR)/test-sqlite.ta