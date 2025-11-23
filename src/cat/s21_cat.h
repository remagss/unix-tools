#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR 1
#define ERROR_INVALID_ARGS 2
#define ERROR_INVALID_SHORT_FLAG 3
#define ERROR_INVALID_GNU_FLAG 4
#define ERROR_FILE_OPEN 5

typedef struct {
  int number_nonblank;  // -b (GNU: --number-nonblank)
  int show_ends;  // -e implies -v (GNU only: -E the same, but without implying
                  // -v)
  int number;     // -n (GNU: --number)
  int squeeze_blank;  // -s (GNU: --squeeze-blank)
  int show_tabs;  // -t implies -v (GNU: -T the same, but without implying -v)
  int show_nonprinting;  // -v
  int show_help;         // --help
} cat_flags;

int run_cat(int argc, char *argv[], cat_flags *flags);
int parse_flags(int argc, char *argv[], cat_flags *flags);
int parse_gnu_flags(char *arg, cat_flags *flags);
int parse_short_flags(char *arg, cat_flags *flags);
void print_file_content(const char *filename, cat_flags *flags);
void handle_error(int error_code, char *argv[]);
void show_help();

#endif