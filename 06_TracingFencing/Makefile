move: move.c
	gcc move.c -o move

unlink_trick.so: unlink_trick.c
	gcc -shared -fPIC unlink_trick.c -o unlink_trick.so 

test: clean move unlink_trick.so
	./move 2>&1 >/dev/null || ([[ $$? == 255 ]] || exit 1)
	@echo "OK: missing arguments"

	./move .__file-not-exists__ output.txt 2>&1 >/dev/null || ([[ $$? == 2 ]] || exit 1)
	@echo "OK: infile not exists"

	mkdir tmp
	echo "qwerty\n123" > tmp/infile.txt
	./move tmp/infile.txt tmp 2>&1 >/dev/null || ([[ $$? == 21 ]] || exit 1)
	@echo "OK: outfile is directory"

	./move tmp/infile.txt tmp/outfile.txt 2>&1 >/dev/null && [ -f tmp/outfile.txt ] && [ ! -f tmp/infile.txt ]
	@echo "OK: success move file"

	echo "qwerty test" > tmp/in-PROTECTED-file.txt
	LD_PRELOAD=unlink_trick.so ./move tmp/in-PROTECTED-file.txt tmp/outfile2.txt && [ -f tmp/in-PROTECTED-file.txt ] && [ -f tmp/outfile2.txt ] 

	@echo "OK: All tests passed"

clean:
	rm -rf move tmp unlink_trick.so
