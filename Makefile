CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wshadow -Werror -g -fsanitize=address -fsanitize=undefined
LDFLAGS = -fsanitize=address -fsanitize=undefined -lm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = raytracer

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -O $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET) > impage.ppm

.PHONY: clean run
