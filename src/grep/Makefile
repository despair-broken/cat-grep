CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_grep

rebuild: clean s21_grep

test: test_grep.sh
	./test_grep.sh

s21_grep: s21_grep.o
	${CC} ${CFLAGS} s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c

clean:
	rm -rf *.o s21_grep
