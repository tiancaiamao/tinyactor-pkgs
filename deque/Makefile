TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-deque.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp deque.ta "$$tmp/core/lib/deque.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-deque.ta

clean:
	true