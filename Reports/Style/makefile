#!/usr/local/bin/tcsh

# To do a separate spell checking of file X.tex, type
# shell> ispell -d british -p X.dict X.tex

report-directory=$(CPHSTL)/Report
language=british #dansk also possible

latex-files:= $(wildcard *.tex)
latex-bases:= $(basename $(latex-files))
pdf-files:= $(addsuffix .pdf, $(latex-bases))

figure-files:= $(wildcard *.fig)
figure-bases:= $(basename $(figure-files))
pdftex-files:= $(addsuffix .pdf, $(figure-bases))
pdf_t-files:= $(addsuffix .pdf_t, $(figure-bases))
scale = 0.60

dictionary-files:= $(addsuffix .dict, $(latex-bases))

default: $(pdf_t-files) $(pdf-files)

.PHONY: article clean copy find spell thesis veryclean

copy:
	cp $(report-directory)/DIKU-article.cls .
	cp $(report-directory)/DIKU-report.cls .
	cp $(report-directory)/DIKU-alternative.bst .
	cp $(report-directory)/DIKU.bst .
	cp $(report-directory)/nat-da.pdf .
	cp $(report-directory)/nat-en.pdf .
	cp $(report-directory)/nat-farve.pdf .


$(pdf-files): %.pdf: %.tex
	pdflatex $*.tex
	bibtex $*
	pdflatex $*.tex
	pdflatex $*.tex
	@cat $*.tex | ispell -d $(language) -p $*.dict -t -l | grep "" && echo "Above words were not in the dictionary." || true
	make -s clean
	
$(pdf_t-files): %.pdf_t: %.fig
	fig2dev -Lpdftex -m$(scale) -p dummy $< > $*.pdf
	fig2dev -Lpdftex_t -m$(scale) -p$*.pdf $< > $*.pdf_t

find :
	find . -type f -print -exec grep $(word) {} \; | less #

clean :
	-rm -f core $(pdf_t-files) $(pdftex-files) a.out *.bak *.log *.aux *.bbl *.blg *.toc *~ .nfs* 2>/dev/null

veryclean : clean
	rm -f *.ps *.pdf 2>/dev/null

