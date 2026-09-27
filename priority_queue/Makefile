TINYACTOR ?= ../tinyactor

.PHONY: test clean

test:
	@set -e; tmp=$$(mktemp -d /tmp/ta-priority_queue.XXXXXX); trap 'rm -rf "$$tmp"' EXIT; rsync -a --exclude='.git' --exclude='.tinyactor-build-*' $(TINYACTOR)/ "$$tmp/core/"; cp priority_queue.ta "$$tmp/core/lib/priority_queue.ta"; cd "$$tmp/core"; ./tinyactor run --no-cache $(CURDIR)/test-priority_queue.ta

clean:
	true