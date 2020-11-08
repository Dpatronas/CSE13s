CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all			:	sequence

sequence	:	sequence.o

	$(CC) -o sequence sequence.o bv.o sieve.o

sequence.o	:	sequence.c

	$(CC) -c sequence.c bv.c sieve.c

clean	:
	rm -f sequence sequence.o bv.o sieve.o

infer	:
	make clean; infer-capture -- make; infer-analyze -- make
	