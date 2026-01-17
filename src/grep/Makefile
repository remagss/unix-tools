CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = s21_grep

SRC_DIR = .
BUILD_DIR = .

SOURCES = $(SRC_DIR)/s21_grep.c $(SRC_DIR)/s21_grep_flags.c
HEADERS = $(SRC_DIR)/s21_grep.h $(SRC_DIR)/s21_grep_flags.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)

test: $(TARGET)
	@echo "Running integration tests..."
	@./tests/run_integration_tests.sh

.PHONY: s21_grep clean rebuild test
