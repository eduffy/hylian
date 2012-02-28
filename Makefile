
all:
	@./waf -j1 build

clean:
	@./waf clean

distclean:
	@./waf distclean
