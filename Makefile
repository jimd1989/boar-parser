.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lm *.c -o "boar-parser"
install:
	mkdir -p $(PREFIX)/bin
	cp boar-parser $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/boar-parser
