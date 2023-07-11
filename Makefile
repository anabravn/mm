main: main.c mm.c mm.h
	gcc main.c mm.c -o main

check: test.c mm.c
	gcc mm.c test.c -o check -lcheck

test: check
	./check

