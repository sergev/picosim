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

test:   tests/build
	$(MAKE) -C tests/build all
	ctest --test-dir tests/build

install: build
	$(MAKE) -C build $@

clean:
	rm -rf build tests/build

build:
	mkdir $@
	cmake -B $@ .

tests/build:
	mkdir $@
	cmake -B $@ tests #-DCMAKE_BUILD_TYPE=Debug
