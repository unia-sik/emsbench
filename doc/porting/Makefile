# $Id: Makefile 395 2015-10-02 14:22:13Z klugeflo $

TARGET=porting

INCLUDES=benv.tex  directories.tex  port.tex

all: $(TARGET).pdf

$(TARGET).pdf: $(TARGET).tex $(INCLUDES)
	pdflatex $<
	pdflatex $<
	pdflatex $< # build three times to ensure that Tikz graphics are correct
