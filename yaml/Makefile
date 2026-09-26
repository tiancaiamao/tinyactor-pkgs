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
OUT := yaml.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): yaml_glue.c src/yaml/api.c src/yaml/parser.c src/yaml/reader.c src/yaml/scanner.c src/yaml/yaml.h src/yaml/yaml_private.h $(TINYACTOR)/ta.h
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) -DYAML_VERSION_STRING=\"0.2.5\" -DYAML_VERSION_MAJOR=0 -DYAML_VERSION_MINOR=2 -DYAML_VERSION_PATCH=5 -Isrc -Isrc/yaml -I$(TINYACTOR) -o $@ yaml_glue.c src/yaml/api.c src/yaml/parser.c src/yaml/reader.c src/yaml/scanner.c

clean:
	rm -f $(OUT)

test: all
	@tmp=$$(mktemp -d /tmp/tinyactor-yaml.XXXXXX); trap 'rm -rf $$tmp' EXIT; \
	cp -R $(TINYACTOR) $$tmp/core; \
	cp yaml.ta $(OUT) $$tmp/core/lib/; \
	cd $$tmp/core && ./tinyactor run --no-cache $(CURDIR)/smoke.ta && ./tinyactor run --no-cache $(CURDIR)/test-yaml.ta