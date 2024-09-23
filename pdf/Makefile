.PHONY: clean all fonts

all: codebook.pdf

codebook.pdf: fonts content.tex codebook.tex
	latexmk --xelatex --shell-escape codebook.tex

clean:
	$(RM) codebook.pdf
	latexmk --xelatex -c codebook.tex || true

fonts: fonts/jf-openhuninn-2.1.ttf

fonts/jf-openhuninn-2.1.ttf:
	wget https://github.com/justfont/open-huninn-font/releases/download/v2.1/jf-openhuninn-2.1.ttf -O $@
