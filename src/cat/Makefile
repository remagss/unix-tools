CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = s21_cat

SRC_DIR = .
BUILD_DIR = .

SOURCES = $(SRC_DIR)/s21_cat.c $(SRC_DIR)/s21_cat_flags.c
HEADERS = $(SRC_DIR)/s21_cat.h $(SRC_DIR)/s21_cat_flags.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)


clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)