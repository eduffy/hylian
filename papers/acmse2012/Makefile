
SHELL = /bin/bash
PAPER  = paper
FIGDIR = figures

TEXCMD=TEXINPUTS=".:latex:" pdflatex

#TEXFILES=\
	$(PAPER).tex			\
	$(wildcard sections/*.tex)	\
	$(wildcard tables/*.tex)

# no deps, always remake if asked
all:
	$(MAKE) -C $(FIGDIR)
	$(TEXCMD) $(PAPER)
	bibtex $(PAPER)
	$(TEXCMD) $(PAPER)
	$(TEXCMD) $(PAPER)

clean:
	$(MAKE) -C $(FIGDIR) clean
	rm -f $(PAPER).{aux,bbl,blg,log,pdf}
