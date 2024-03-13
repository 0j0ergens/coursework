.PHONY: clean

lab3: lab3.h lab3.c
	clang -Wall -c lab3.c
test: lab3.h lab3.c test.c
	clang -Wall -o test lab3.c test.c -lcriterion
clean:
	rm -rf a.out lab3 lab3.o
