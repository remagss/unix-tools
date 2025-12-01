CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = s21_grep

SRC_DIR = .
BUILD_DIR = .

SOURCES = $(SRC_DIR)/s21_grep.c
HEADERS = $(SRC_DIR)/s21_grep.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)


clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)

.PHONY: s21_grep clean rebuild test