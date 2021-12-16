all: guess ru/LC_MESSAGES/guess.mo

guess: guess.c
	gcc $< -o $@

guess.pot: guess.c
	xgettext -k_ -c $< -o new.pot
	msgmerge -U $@ new.pot

guess.po: guess.pot
	msgmerge -U $@ $<

ru/LC_MESSAGES/guess.mo: guess.po
	mkdir -p ru/LC_MESSAGES
	msgfmt $< -o $@

docs: guess.c Doxyfile
	doxygen

man: guess
	help2man --version-string=1.0 ./guess > guess.man

clean:
	rm -rf ru/ new.pot guess guess.man html/ latex/
