# Author:
#      Wim Looman
# Copyright:
#      Copyright (c) 2010 Wim Looman
# License:
#      GNU General Public License (see http://www.gnu.org/licenses/gpl-3.0.txt)

## User interface, just set the main filename and it will do everything for you
# If you have any extra code or images included list them in EXTRA_FILES
# This should work as long as you have all the .tex, .sty and .bib files in
# the same folder.
MAINFILE = doc
EXTRA_FILES := $(shell echo "img/*")

## Inner workings
OBJECTS = $(shell echo *.tex)
STYLES = $(shell echo *.sty)
BIB = $(shell echo *.bib)

OBJECTS_TEST = $(addsuffix .t, $(basename $(OBJECTS)))
STYLES_TEST = $(addsuffix .s, $(basename $(STYLES)))
BIB_TEST = bib
TESTS = $(addprefix make/, $(OBJECTS_TEST) $(STYLES_TEST))
TEMP2 := $(shell mkdir make 2>/dev/null)

.PHONY: all
all: $(MAINFILE).pdf


$(MAINFILE).pdf: $(TESTS) $(EXTRA_FILES)
	for number in 1 2 3 4 5 6; do \
		makeglossaries $(MAINFILE); \
		latexmk -pdf --synctex=1 -interaction=nonstopmode  -file-line-error  $(MAINFILE); \
	done

make/%.t: %.tex
	touch $@

make/%.s: %.sty
	touch $@

# make/bib: $(BIB)
# 	latex $(MAINFILE)
# 	bibtex $(MAINFILE)
# 	touch $@

.PHONY: clean
clean:
	-rm -f *.aux
	-rm -f *.log
	-rm -f *.glo
	-rm -f *.glsdefs
	-rm -f *.synctex.gz
	-rm -f *.ist
	-rm -f *.fls
	-rm -f *.glg
	-rm -f *.gls
	-rm -f *.fdb_latexmk
	-rm -f *.toc
	-rm -f *.bbl
	-rm -f *.pdf
	-rm -f *.ps
	-rm -f *.dvi
	-rm -f *.blg
	-rm -f *.out
	-rm -f make/bib
	-rm -rf ./make

.PHONY: cleanall
cleanall: clean
	-rm -f *.pdf
	-rm -f *.ps
	-rm -f *.dvi
	-rm -rf ./make
