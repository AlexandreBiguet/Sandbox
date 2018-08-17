.SUFFIXES:

all:
	pdflatex main.tex

standalone:
	pdflatex stan1.tex
	pdflatex stan2.tex

clean:
	rm -f *.aux *.log *.nav *.out *.snm *.toc

cleanall: clean
	rm -f *.pdf
