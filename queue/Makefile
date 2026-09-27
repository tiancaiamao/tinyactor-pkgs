TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-queue.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp queue.ta "$$tmp/core/lib/queue.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-queue.ta

clean:
	true