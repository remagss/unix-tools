#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR 1
#define ERROR_INVALID_ARGS 2
#define ERROR_FILE_OPEN 3
#define ERROR_INVALID_FLAG 4
#define ERROR_REGEX_COMPILE 5

#define MAX_PATTERNS 100
#define MAX_LINE_LENGTH 4096

typedef struct {
  int ignore_case;       // -i
  int invert_match;      // -v
  int count_only;        // -c
  int files_with_match;  // -l
  int line_number;       // -n
  char patterns[MAX_PATTERNS][MAX_LINE_LENGTH];
  int pattern_count;
} grep_flags;

int run_grep(int argc, char *argv[], grep_flags *flags);
int parse_flags(int argc, char *argv[], grep_flags *flags);
int process_flag_argument(int argc, char *argv[], int *i, grep_flags *flags,
                          int *pattern_found);
int process_e_flag(int argc, char *argv[], int *i, grep_flags *flags,
                   int *pattern_found);
int parse_short_flags(char *arg, grep_flags *flags);
int process_file(const char *filename, grep_flags *flags, int multiple_files);
void handle_error(int error_code, char *argv[]);

#endif
