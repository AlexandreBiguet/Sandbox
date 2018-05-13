.SUFFIXES :

compil: test.tex
	latex test.tex

metafont : 
	mf '\mode:=localfont; input fmftempl'

clean : 
	rm -f *.mf *.dvi *.pdf *.aux *.log *.out

all : compil metafont compil
