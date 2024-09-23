.PHONY: clean all

all: codebook.pdf

codebook.pdf: content.tex codebook.tex
	latexmk --xelatex --shell-escape codebook.tex

clean:
	$(RM) codebook.pdf
	latexmk --xelatex -c codebook.tex || true
