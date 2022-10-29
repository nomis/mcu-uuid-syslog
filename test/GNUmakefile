.PHONY: all build doxygen

all: build doxygen
	python3 version_check.py

build:
	rm -rf build/*/.pio
	# Workaround for https://github.com/platformio/platformio-core/issues/2573
	cd build/example-Example && pio lib install --no-save nomis/uuid-common nomis/uuid-log
	platformio run -d build/example-Example
	build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_0/program >build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_0/Example.txt
	build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_1/program >build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_1/Example.txt
	build/example-Example/.pio/build/native/program >../examples/Example.txt
	cmp build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_0/Example.txt ../examples/Example.txt
	cmp build/example-Example/.pio/build/native_STD_MUTEX_AVAILABLE_1/Example.txt ../examples/Example.txt

doxygen:
	wget https://raw.githubusercontent.com/nomis/mcu-uuid-doxygen/main/Doxyfile -O Doxyfile
	rm -rf html
	(cat Doxyfile; echo INPUT += ../src) | doxygen - 1>doxygen.out 2>doxygen.err
	cat doxygen.err
	cmp /dev/null doxygen.err
