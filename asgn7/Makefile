CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

TARGET_ENC := encode
TARGET_ENC_SRC := encode.c io.c trie.c word.c 
OBJ_ENC := $(patsubst %.c,%.o,$(TARGET_ENC_SRC))

TARGET_DEC := decode
TARGET_DEC_SRC := decode.c io.c trie.c word.c
OBJ_DEC := $(patsubst %.c,%.o,$(TARGET_DEC_SRC))

all: $(TARGET_ENC) $(TARGET_DEC)

$(TARGET_ENC): $(OBJ_ENC)

	$(CC) -o $@ ${OBJ_ENC}

$(TARGET_DEC): $(OBJ_DEC)

	$(CC) -o $@ ${OBJ_DEC}

%.o: %.c

	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET_ENC) $(TARGET_DEC) *.o

infer:
	make clean; infer-capture -- make; infer-analyze -- make

