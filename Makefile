.PHONY: all clean cleanall makefiles makefiles-lib checkmakefiles


all: checkmakefiles
	+$(MAKE) -C src all

clean: checkmakefiles
	+$(MAKE) -C src clean

cleanall: checkmakefiles
	@+$(MAKE) -C src MODE=release clean
	@+$(MAKE) -C src MODE=debug clean

MAKEMAKE_OPTIONS := -f --deep -o matlab-scheduler -O out \
	-I. \
	-I$$MCR_ROOT/extern/include \
	-L$$MCR_ROOT/runtime/glnxa64 \
	-L$$MCR_ROOT/bin/glnxa64

makefiles: makefiles-lib

makefiles-lib:
	cd src && opp_makemake --make-lib $(MAKEMAKE_OPTIONS)

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '========================================================================'; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '========================================================================'; \
	echo; \
	exit 1; \
	fi
