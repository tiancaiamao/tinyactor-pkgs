TINYACTOR ?= ../tinyactor

.PHONY: test clean
test:
	cp queue.ta $(TINYACTOR)/lib/queue.ta
	cd $(TINYACTOR) && ./tinyactor run --no-cache $(CURDIR)/test-queue.ta

clean:
	true