build: range.c
	gcc -O0 -g range.c -o range

test:
	gdb -x test_1_12.gdb --quiet --batch --args ./range 1 12 | grep -oP '@@@\K.*' | diff - test_1_12.answer
	gdb -x test_-100_100_3.gdb --quiet --batch --args ./range -100 100 3 | grep -oP '@@@\K.*' | diff - test_-100_100_3.answer

clean:
	rm -rf range range.dSYM
