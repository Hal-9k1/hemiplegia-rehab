HOST :=
PICO := controller

clean_host_targets := $(addprefix clean-,$(HOST))
clean_host_targets := $(addprefix clean-,$(PICO))

.PHONY: all client clean distclean pico-sdk $(clean_host_targets) $(clean_pico_targets)

all: $(HOST) $(PICO)

$(HOST): %: %/%
	$(MAKE) -C $@

$(PICO): pico-sdk/.makestamp
	mkdir -p pico-build/$@
	cmake -DPICO_SDK_PATH=$(realpath ./pico-sdk) -S $@ -B pico-build/$@
	cmake --build pico-build/$@

pico-sdk: pico-sdk/.makestamp

pico-sdk/.makestamp:
	git clone https://github.com/raspberrypi/pico-sdk.git --depth=1 pico-sdk
	git -C pico-sdk submodule update --init --depth=1 --progress --recursive
	touch pico-sdk/.makestamp

$(clean_host_targets):
	$(MAKE) -C $(@:clean-%=%) clean

$(clean_pico_targets):
	cmake --build pico-build/$(@:clean-%=%) --target clean || true

clean: $(clean_host_targets) $(clean_pico_targets)

distclean: $(clean_host_targets)
	rm -rf pico-build pico-sdk || true
