TARGET = sorting

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

OBJ:= $(patsubst %.c,%.o,$(wildcard *.c))

all: $(TARGET)

$(TARGET): $(OBJ)

	$(CC) -o $@ ${OBJ}

%.o: %.c

	$(CC) $(CFLAGS) -o $@ -c $<

valgrind:
	valgrind ./$(TARGET)

clean:
	rm -f $(TARGET) *.o

infer:
	make clean; infer-capture -- make; infer-analyze -- make
