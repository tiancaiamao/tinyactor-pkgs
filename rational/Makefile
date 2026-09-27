TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-rational.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp ../num_internal/num_internal.ta "$$tmp/core/lib/num_internal.ta"; cp rational.ta "$$tmp/core/lib/rational.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-rational.ta

clean:
	true