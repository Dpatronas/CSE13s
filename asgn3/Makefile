CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all	:	tower

tower	:	tower.o

	$(CC) -o tower tower.o stack.o

tower.o	:	tower.c

	$(CC) -c tower.c stack.c

clean	:
	rm -f tower tower.o stack.o

infer	:
	make clean; infer-capture -- make; infer-analyze -- make