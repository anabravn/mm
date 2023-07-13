main: main.c mm.c mm.h
	gcc main.c mm.c -o main -Wall

check: test.c mm.c
	gcc mm.c test.c -o check -lcheck -Wall

test: check
	./check

