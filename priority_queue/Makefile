TINYACTOR ?= ../tinyactor

.PHONY: test clean
test:
	cp priority_queue.ta $(TINYACTOR)/lib/priority_queue.ta
	cd $(TINYACTOR) && ./tinyactor run --no-cache $(CURDIR)/test-priority_queue.ta

clean:
	true