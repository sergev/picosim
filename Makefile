#
# make
# make all      -- build everything
#
# make test     -- run unit tests
#
# make install  -- install picosim binaries to /usr/local
#
# make clean    -- remove build files
#

all:    build
	$(MAKE) -C build $@

test:   build
	$(MAKE) -C build test

install: build
	$(MAKE) -C build $@

clean:
	rm -rf build

build:
	mkdir $@
	cmake -B $@ .

#
# Build and install SystemC library.
#
systemc: /usr/local/include/systemc.h

#
# The SystemC library is sensitive to the C++ standard.
# It must be compiled with option -std=c++17, to match the simulator.
#
/usr/local/include/systemc.h:
	wget https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz
	tar xzf systemc-2.3.3.tar.gz
	cd systemc-2.3.3
	mkdir build
	cd build
	cmake .. -DCMAKE_CXX_STANDARD=17 -DDISABLE_COPYRIGHT_MESSAGE=ON -DCMAKE_INSTALL_PREFIX=/usr/local
	make
	make install

.PHONY: clean test install
