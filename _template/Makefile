# Reference package: a minimal C module + TA glue + a self-contained smoke test.
#
# The package is also its own consumer project: the `tinyactor.deps` written by
# the `test` recipe maps the tree name `example.org/template` back to this
# directory, so nothing has to be copied into the core tree. The dylib is found
# by the runtime's cwd-relative lookup (`lib/template.<ext>`), hence the smoke
# runs from this directory.
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

OUT := lib/template.$(EXT)

.PHONY: all clean test
all: $(OUT)

$(OUT): template.c $(TINYACTOR)/ta.h
	@mkdir -p lib
	$(CC) -Wall -Wextra -std=c99 -O2 -fPIC -shared $(SHARED_FLAGS) -I$(TINYACTOR) -o $@ template.c

# deps 由这里生成：TINYACTOR 可以被命令行覆盖（例如指向 /tmp 的一次性核心副本），
# 写死路径的 tinyactor.deps 覆盖后就指错了树。
test: all
	printf 'tinyactor\t%s\nexample.org/template\t.\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	$(TINYACTOR)/tinyactor run smoke.ta

clean:
	rm -rf lib vendor tinyactor.deps tinyactor.lock