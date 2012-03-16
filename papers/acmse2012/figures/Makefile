
DIAFILES=\
	$(wildcard *.dia)

PLOTFILES=\
	$(wildcard *.plot)

EPSFILES=\
	$(DIAFILES:.dia=.eps)\
	$(PLOTFILES:.plot=.eps)

# This is for generated PDFs only!
PDFFILES=\
	$(sort $(EPSFILES:.eps=.pdf))

all: $(PDFFILES)

%.pdf: %.eps
	epstopdf $<

%.eps: %.dia
	dia --export=$@ --filter=eps $<

%.eps: %.plot %.dat
	gnuplot $<

clean:
	rm -f $(PDFFILES) $(EPSFILES)
	rm -f $(addsuffix ~, $(DIAFILES))
