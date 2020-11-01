CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:	tower

tower:	tower.o stack.o stack.c
		$(CC) -o tower tower.o stack.o stack.c

tower.o:	tower.c stack.o stack.c
		$(CC) $(CFLAGS) -c tower.c stack.c stack.o

clean:	
		rm -rf tower tower.c stack.c stack.o infer-out

infer:	
		make clean; infer-capture -- make; infer-analyze -- make