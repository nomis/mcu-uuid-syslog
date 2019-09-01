.PHONY: all build

all: build
	python3 version_check.py

build:
	rm -rf build/*/.pio
	# Workaround for https://github.com/platformio/platformio-core/issues/2573
	cd build/example-Example && pio lib install uuid-common uuid-log
	platformio run -d build/example-Example
