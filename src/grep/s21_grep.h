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

#define MAX_PATTERNS 100
#define MAX_LINE_LENGTH 4096

typedef struct {
  int e;  // pattern (-e)
  int i;  // ignore uppercase vs lowercase (-i)
  int v;  // invert match (-v)
  int c;  // output count of matching lines only (-c)
  int l;  // output matching files only (-l)
  int n;  // precede each matching line with a line number (-n)
  // int h;  // output matching lines without preceding them by file names (-h)
  // int s;  // suppress error messages about nonexistent or unreadable files
  // int f;  // take regexes from a file (-f [file])
  // int o;  // output the matched parts of a matching line (-o)

  int show_help;  // --help
  int pattern_count; // count of patterns
  char *patterns[MAX_PATTERNS]; // array of patterns
  char *pattern_files[MAX_PATTERNS]; // files with patterns
  int pattern_files_count;
} grep_flags;

int run_grep(int argc, char *argv[], grep_flags *flags);
int parse_flags(int argc, char *argv[], grep_flags *flags);
int parse_gnu_flag(char *arg, grep_flags *flags);
int parse_short_flags(char *arg, grep_flags *flags, int *arg_index, 
                      int argc, char *argv[]);
void handle_error(int error_code, char *argv[]);
void free_patterns(grep_flags *flags);
int add_pattern(grep_flags *flags, const char *pattern);

#endif