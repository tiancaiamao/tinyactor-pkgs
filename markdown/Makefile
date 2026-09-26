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
OUT := markdown.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): markdown_glue.c src/md4c/md4c.c src/md4c/md4c.h $(TINYACTOR)/ta.h
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) -I$(TINYACTOR) -Isrc -o $@ markdown_glue.c src/md4c/md4c.c

clean:
	rm -f $(OUT)

test: all
	@tmp=$$(mktemp -d /tmp/tinyactor-markdown.XXXXXX); trap 'rm -rf $$tmp' EXIT; \
	cp -R $(TINYACTOR) $$tmp/core; \
	cp markdown.ta $(OUT) $$tmp/core/lib/; \
	cd $$tmp/core && ./tinyactor run --no-cache $(CURDIR)/smoke.ta && ./tinyactor run --no-cache $(CURDIR)/test-markdown.ta