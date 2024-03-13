.PHONY: clean

test: hw5.h hw5.c hw5-phase1-autograder.c
	clang -o test hw5.c hw5-phase1-autograder.c -lcriterion
clean:
	rm -rf a.out test
