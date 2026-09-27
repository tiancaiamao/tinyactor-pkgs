TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-num_internal.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp num_internal.ta "$$tmp/core/lib/num_internal.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-num_internal.ta

clean:
	true