HOST :=
PICO := controller
INSTALL_PATH := /cygdrive/d
SERIAL_PATH := /dev/ttyS2

clean_host_targets := $(addprefix clean-,$(HOST))
clean_pico_targets := $(addprefix clean-,$(PICO))
install_pico_targets := $(addprefix flash-,$(PICO))
pico_makefiles := $(PICO:%=pico-build/%/Makefile)

.PHONY: all client clean distclean pico-sdk serial $(HOST) $(PICO) $(clean_host_targets)\
	$(clean_pico_targets) $(install_pico_targets)

all: $(HOST) $(PICO)

$(HOST): %: %/%
	$(MAKE) -C $@

$(PICO): %: pico-build/%/Makefile
	cmake --build pico-build/$@

$(pico_makefiles): pico-sdk/.makestamp
	mkdir -p pico-build/$(@:pico-build/%/Makefile=%)
	cmake -S $(@:pico-build/%/Makefile=%) -B pico-build/$(@:pico-build/%/Makefile=%)

$(install_pico_targets): flash-%: %
	cp pico-build/$(@:flash-%=%)/$(@:flash-%=%).uf2 $(INSTALL_PATH)

pico-sdk: pico-sdk/.makestamp

pico-sdk/.makestamp:
	git clone https://github.com/raspberrypi/pico-sdk.git --depth=1 pico-sdk
	git -C pico-sdk submodule update --init --depth=1 --progress --recursive
	touch pico-sdk/.makestamp

serial:
	screen screen -m $(SERIAL_PATH)

$(clean_host_targets):
	$(MAKE) -C $(@:clean-%=%) clean

$(clean_pico_targets):
	cmake --build pico-build/$(@:clean-%=%) --target clean || true

clean: $(clean_host_targets) $(clean_pico_targets)

distclean: $(clean_host_targets)
	rm -rf pico-build pico-sdk || true
