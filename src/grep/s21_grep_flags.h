#ifndef S21_GREP_FLAGS_H
#define S21_GREP_FLAGS_H

#include "s21_grep.h"

void add_pattern(grep_flags *flags, const char *pattern);
int count_files(int argc, char *argv[], grep_flags *flags);
int process_file(const char *filename, grep_flags *flags, int multiple_files);
int search_in_file(FILE *file, grep_flags *flags, const char *filename,
                   int multiple_files);
int compile_regexes(grep_flags *flags, regex_t **regex_array,
                    int **regex_compiled);
int compile_all_patterns(grep_flags *flags, regex_t *regex_array,
                         int *regex_compiled);
int process_lines(FILE *file, grep_flags *flags, const char *filename,
                  int multiple_files, regex_t *regex_array,
                  int *regex_compiled);
void print_results(const char *filename, grep_flags *flags, int multiple_files,
                   int match_count);
void cleanup_regexes(regex_t *regex_array, int *regex_compiled,
                     int pattern_count);
void free_regex_array(regex_t *regex_array, int *regex_compiled,
                      int pattern_count);
int compile_regex(regex_t *regex, const char *pattern, int ignore_case);
int match_line(const char *line, regex_t *regex, int invert_match);
int match_any_pattern(const char *line, regex_t *regex_array,
                      int *regex_compiled, int pattern_count, int invert_match);
void print_match(const char *line, const char *filename, int line_num,
                 grep_flags *flags, int multiple_files, int match_count);
void print_count(const char *filename, int count, int multiple_files);
int is_file_argument(int argc, char *argv[], int index, grep_flags *flags);
int is_pattern_in_flags(const char *arg, grep_flags *flags);

#endif
