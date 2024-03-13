.PHONY: clean

test: hw7.h hw7.c hw7-phase1-autograder.c
	clang -Wall -o test -lm hw7.c hw7-phase1-autograder.c -lcriterion

clean:
	rm -rf a.out test
