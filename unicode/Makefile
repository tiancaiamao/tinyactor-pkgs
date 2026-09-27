TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-unicode.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp unicode.ta "$$tmp/core/lib/unicode.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-unicode.ta

clean:
	true