.PHONY: rep clean

FILE = main

rep:
	xelatex -synctex=1 -interaction=nonstopmode $(FILE).tex
	bibtex $(FILE).aux
	xelatex -synctex=1 -interaction=nonstopmode $(FILE).tex
	xelatex -synctex=1 -interaction=nonstopmode $(FILE).tex

clean:
	rm *.aux *.bbl *.blg *.log *.out *.toc pages/*.aux inc/*.aux inc/*.bbl inc/*.blg inc/*.log inc/*.out inc/*.toc
	echo "Clear:Ready"
