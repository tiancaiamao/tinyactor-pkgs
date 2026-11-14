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
OUT := lib/yaml.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): yaml_glue.c src/yaml/api.c src/yaml/parser.c src/yaml/reader.c src/yaml/scanner.c src/yaml/yaml.h src/yaml/yaml_private.h $(TINYACTOR)/ta.h | lib
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) -DYAML_VERSION_STRING=\"0.2.5\" -DYAML_VERSION_MAJOR=0 -DYAML_VERSION_MINOR=2 -DYAML_VERSION_PATCH=5 -Isrc -Isrc/yaml -I$(TINYACTOR) -o $@ yaml_glue.c src/yaml/api.c src/yaml/parser.c src/yaml/reader.c src/yaml/scanner.c

lib:
	mkdir -p lib

# 运行期按 cwd 相对路径找 lib/yaml.$(EXT)，所以测试在包目录里跑。
test: all
	printf 'tinyactor\t%s\ntinyactor-pkgs\t..\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	$(TINYACTOR)/tinyactor run smoke.ta
	$(TINYACTOR)/tinyactor run test-yaml.ta

clean:
	rm -rf lib vendor tinyactor.deps tinyactor.lock