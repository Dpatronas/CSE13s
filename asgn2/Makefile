CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:	math

math:	math.o
		$(CC) -o math math.o

math.o:	math.c
		$(CC) $(CFLAGS) -c math.c

clean:	
		rm -rf math math.c infer-out

infer:	
		make clean; infer-capture -- make; infer-analyze -- make