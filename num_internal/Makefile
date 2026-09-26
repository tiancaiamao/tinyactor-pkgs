TINYACTOR ?= /tmp/b8num-core
.PHONY: test
test:
	cp ../num_internal/num_internal.ta $(TINYACTOR)/lib/num_internal.ta
	cd $(TINYACTOR) && ./tinyactor run --no-cache $(CURDIR)/test-num_internal.ta