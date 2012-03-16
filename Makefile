
all:
	@./waf -j1 build

dist:
	@./waf dist

clean:
	@./waf clean

distclean:
	@./waf distclean
