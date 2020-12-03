CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g

TARGET_ENC := encode.c
TARGET_DEC := decode.c

OBJ_ENC := $(patsubst %.c,%.o,$(TARGET_ENC))
OBJ_DEC := $(patsubst %.c,%.o,$(TARGET_DEC))

all: $(TARGET_ENC) $(TARGET_DEC)

$(TARGET_ENC): $(OBJ_ENC)

	$(CC) -o $@ ${OBJ_ENC}

$(TARGET_DEC): $(OBJ_DEC)

	$(CC) -o $@ ${OBJ_DEC}

%.o: %.c

	$(CC) $(CFLAGS) -o $@ -c $<

valgrind:
	valgrind ./$(TARGET_ENC) $(TARGET_DEC)

clean:
	rm -f $(TARGET_ENC) $(TARGET_DEC) *.o

infer:
	make clean; infer-capture -- make; infer-analyze -- make
