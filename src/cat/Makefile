CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_cat

rebuild: clean s21_cat

test: ./my_test.sh
	./my_test.sh

s21_cat: s21_cat.o
	${CC} ${CFLAGS} s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c

clean:
	rm -rf *.o s21_cat