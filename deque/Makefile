TINYACTOR ?= ../tinyactor

.PHONY: test clean
test:
	cp deque.ta $(TINYACTOR)/lib/deque.ta
	cd $(TINYACTOR) && ./tinyactor run --no-cache $(CURDIR)/test-deque.ta

clean:
	true