
all:
	@./waf -j1 build

dist:
	@./waf dist

install:
	@./waf install

clean:
	@./waf clean

distclean:
	@./waf distclean
