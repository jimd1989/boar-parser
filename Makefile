.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lm src/boari/*.c -o "boari"
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lsndio -lm -pthread src/boar/*.c -o "boar"
boari:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lm src/boari/*.c -o "boari"
boar:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -lsndio -lm -pthread src/boar/*.c -o "boar"
install:
	mkdir -p $(PREFIX)/bin
	cp boari $(PREFIX)/bin
	cp boar $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/boari
	rm $(PREFIX)/bin/boar
