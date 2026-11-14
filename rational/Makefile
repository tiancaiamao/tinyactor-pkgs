# 纯 TA 包（无 C 构建）。测法：把自己当消费树，vendor 两份依赖再跑行为测试。
TINYACTOR ?= ../../tinyactor

.PHONY: test clean

test:
	printf 'tinyactor\t%s\ntinyactor-pkgs\t..\n' '$(TINYACTOR)' > tinyactor.deps
	$(TINYACTOR)/tinyactor vendor
	$(TINYACTOR)/tinyactor run test-rational.ta

clean:
	rm -rf vendor tinyactor.deps tinyactor.lock
