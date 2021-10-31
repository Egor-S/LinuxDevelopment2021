DUMP=>/dev/null 2>&1

move: move.c
	gcc move.c -o move

unlink_trick.so: unlink_trick.c
	gcc -shared -fPIC unlink_trick.c -o unlink_trick.so 

test: clean move unlink_trick.so
	@./move ${DUMP} || ([[ $$? == 255 ]] || exit 1)
	@echo "OK: missing arguments"

	@./move .__file-not-exists__ output.txt ${DUMP} || ([[ $$? == 2 ]] || exit 1)
	@echo "OK: infile not exists"

	@mkdir tmp
	@echo "qwerty\n123" > tmp/infile.txt
	@./move tmp/infile.txt tmp ${DUMP} || ([[ $$? == 21 ]] || exit 1)
	@echo "OK: outfile is directory"

	@./move tmp/infile.txt tmp/outfile.txt ${DUMP} && [ -f tmp/outfile.txt ] && [ ! -f tmp/infile.txt ]
	@echo "OK: success move file"

	@echo "qwerty test" > tmp/in-PROTECT-file.txt
	@(LD_PRELOAD=./unlink_trick.so ./move tmp/in-PROTECT-file.txt tmp/outfile2.txt ${DUMP} || ([[ $$? == 13 ]] || exit 1)) && [ -f tmp/in-PROTECT-file.txt ] && [ -f tmp/outfile2.txt ]
	@echo "OK: can't delete PROTECT file"

	@(strace -e fault=write:error=EIO ./move tmp/in-PROTECT-file.txt tmp/outfile3.txt ${DUMP} || [[ $$? == 5 ]]) && [ -f tmp/in-PROTECT-file.txt ] && [ ! -f tmp/outfile3.txt ]
	@echo "OK: write fails (strace injected EIO)"

	@echo "All OK: tests passed"

clean:
	rm -rf move tmp unlink_trick.so
