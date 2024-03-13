all: test

test: test.c smalloc.c
	gcc -g -o test test.c smalloc.c -I. -Werror

clean:
	rm -f test
