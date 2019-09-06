.PHONY: all build doxygen

all: build doxygen
	python3 version_check.py

build:
	rm -rf build/*/.pio
	# Workaround for https://github.com/platformio/platformio-core/issues/2573
	cd build/example-Example && pio lib install uuid-common uuid-log
	platformio run -d build/example-Example

doxygen:
	wget https://raw.githubusercontent.com/nomis/mcu-uuid-doxygen/master/Doxyfile -O Doxyfile
	rm -rf html
	doxygen
