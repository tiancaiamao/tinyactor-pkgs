TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-regexp.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp regexp.ta "$$tmp/core/lib/regexp.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-regexp.ta

clean:
	true