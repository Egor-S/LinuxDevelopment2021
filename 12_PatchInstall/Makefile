PREFIX ?= /usr
DESTDIR=
BIN=$(DESTDIR)$(PREFIX)/bin
SHARE=$(DESTDIR)$(PREFIX)/share
LOCALEDIR ?= $(PREFIX)/share/locale

all: guess ru/LC_MESSAGES/guess.mo man

guess: guess.c
	gcc -DLOCALEDIR='"$(LOCALEDIR)"' $< -o $@

guess.pot: guess.c
	xgettext -k_ -c $< -o new.pot
	msgmerge -U $@ new.pot

guess.po: guess.pot
	msgmerge -U $@ $<

ru/LC_MESSAGES/guess.mo: guess.po
	mkdir -p ru/LC_MESSAGES
	msgfmt $< -o $@

man: guess
	help2man --version-string=1.0 ./guess > guess.man

install: all
	mkdir -p $(BIN)
	mkdir -p $(SHARE)/locale
	mkdir -p $(SHARE)/man/man1
	cp guess $(BIN)/guess
	cp -r ru/ $(SHARE)/locale/.
	cp guess.man $(SHARE)/man/man1/guess.man

clean:
	rm -rf ru/ new.pot guess guess.man html/ latex/
