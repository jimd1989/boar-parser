.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lm src/*.c -o "boari"
install:
	mkdir -p $(PREFIX)/bin
	cp boari $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/boari
