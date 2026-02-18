## Dependencies
* GNU Make
* CMake
* Toolchain for your host machine
* Toolchain for `arm-none-eabi`
* lots of spare time

This goes a lot smoother if you're using Linux or WSL. Cygwin and MinGW work but the ARM toolchain isn't prebuilt, so you'll spend another hour figuring out the right build options to compile it from source through trial and error.
## Building
If you plan on running this, you should probably open a screen or tmux window and run `make pico-sdk` like, right now. The Pico SDK will download automatically but is huge. Luckily it only needs to do this once unless you remove the `pico-sdk` directory, so... don't do that.
* pico targets: build code for the Pico. Install it by mounting the Pico as a USB device by resetting it/powering it on while holding BOOTSEL, and moving `pico-build/<TARGET>/*.uf2` there. The Pico will dismount automatically and start running the code.
* host targets: build host-side code, usually for debugging or other utilities. These produce binaries for your host machine.
