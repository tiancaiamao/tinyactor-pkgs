TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-decimal.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp ../num_internal/num_internal.ta "$$tmp/core/lib/num_internal.ta"; cp decimal.ta "$$tmp/core/lib/decimal.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-decimal.ta

clean:
	true