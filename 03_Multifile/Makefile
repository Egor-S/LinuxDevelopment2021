GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.* *.test
CFLAGS = -fPIC

all: README prog prog-a prog-so

prog: const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. $< -loutput -o $@

README: prog
	./$< 2> $@

test: prog prog-a prog-so
	# for file in $^; do ./$$file 2> $$file-0.test; done
	for file in $^; do ./$$file qwerty > $$file-1.test; done
	for file in $^; do ./$$file foo --bar test > $$file-3.test; done
	for c in 1 3; do cmp prog-$$c.test prog-a-$$c.test && cmp prog-$$c.test prog-so-$$c.test; done

fun.o: outlib.h

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)
