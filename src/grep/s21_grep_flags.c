#include "s21_grep_flags.h"

#include <stdlib.h>

int is_file_argument(int argc, char *argv[], int index, grep_flags *flags) {
  int is_file = 0;
  (void)argc;

  if (argv[index][0] != '-' && strcmp(argv[index], "-") != 0) {
    if (index > 0 && strcmp(argv[index - 1], "-e") == 0) {
      is_file = 0;
    } else {
      is_file = !is_pattern_in_flags(argv[index], flags);
    }
  }

  return is_file;
}

int is_pattern_in_flags(const char *arg, grep_flags *flags) {
  int is_pattern = 0;

  for (int i = 0; i < flags->pattern_count; i++) {
    if (strcmp(arg, flags->patterns[i]) == 0) {
      is_pattern = 1;
      break;
    }
  }

  return is_pattern;
}

void add_pattern(grep_flags *flags, const char *pattern) {
  if (flags->pattern_count < MAX_PATTERNS) {
    strncpy(flags->patterns[flags->pattern_count], pattern,
            MAX_LINE_LENGTH - 1);
    flags->patterns[flags->pattern_count][MAX_LINE_LENGTH - 1] = '\0';
    flags->pattern_count++;
  }
}

int count_files(int argc, char *argv[], grep_flags *flags) {
  int count = 0;

  for (int i = 1; i < argc; i++) {
    if (is_file_argument(argc, argv, i, flags)) {
      count++;
    }
  }

  return count;
}

int process_file(const char *filename, grep_flags *flags, int multiple_files) {
  int status_flag = SUCCESS;
  FILE *file = fopen(filename, "r");
  char *error_argv[] = {(char *)filename, NULL};

  if (file == NULL) {
    status_flag = ERROR_FILE_OPEN;
    handle_error(status_flag, error_argv);
  } else {
    search_in_file(file, flags, filename, multiple_files);
    fclose(file);
  }

  return status_flag;
}

int search_in_file(FILE *file, grep_flags *flags, const char *filename,
                   int multiple_files) {
  regex_t *regex_array = NULL;
  int *regex_compiled = NULL;
  int compiled_count = 0;
  int match_count = 0;

  compiled_count = compile_regexes(flags, &regex_array, &regex_compiled);

  if (compiled_count > 0) {
    match_count = process_lines(file, flags, filename, multiple_files,
                                regex_array, regex_compiled);
  }

  print_results(filename, flags, multiple_files, match_count);
  cleanup_regexes(regex_array, regex_compiled, flags->pattern_count);

  return SUCCESS;
}

int compile_regexes(grep_flags *flags, regex_t **regex_array,
                    int **regex_compiled) {
  int compiled_count = 0;

  if (flags->pattern_count > 0) {
    *regex_array = malloc(flags->pattern_count * sizeof(regex_t));
    *regex_compiled = malloc(flags->pattern_count * sizeof(int));

    if (*regex_array != NULL && *regex_compiled != NULL) {
      compiled_count =
          compile_all_patterns(flags, *regex_array, *regex_compiled);
    }
  }

  return compiled_count;
}

int compile_all_patterns(grep_flags *flags, regex_t *regex_array,
                         int *regex_compiled) {
  int compiled_count = 0;

  for (int i = 0; i < flags->pattern_count; i++) {
    int compile_status =
        compile_regex(&regex_array[i], flags->patterns[i], flags->ignore_case);
    regex_compiled[i] = (compile_status == 0) ? 1 : 0;
    if (regex_compiled[i]) {
      compiled_count++;
    }
  }

  return compiled_count;
}

int process_lines(FILE *file, grep_flags *flags, const char *filename,
                  int multiple_files, regex_t *regex_array,
                  int *regex_compiled) {
  char line[MAX_LINE_LENGTH];
  int line_num = 0;
  int match_count = 0;

  while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
    line_num++;
    int matched = match_any_pattern(line, regex_array, regex_compiled,
                                    flags->pattern_count, flags->invert_match);

    if (matched) {
      match_count++;
      print_match(line, filename, line_num, flags, multiple_files, match_count);
    }
  }

  return match_count;
}

void print_results(const char *filename, grep_flags *flags, int multiple_files,
                   int match_count) {
  if (flags->count_only) {
    print_count(filename, match_count, multiple_files);
  }

  if (flags->files_with_match && match_count > 0) {
    printf("%s\n", filename);
  }
}

void cleanup_regexes(regex_t *regex_array, int *regex_compiled,
                     int pattern_count) {
  if (regex_array != NULL) {
    free_regex_array(regex_array, regex_compiled, pattern_count);
    free(regex_array);
  }

  if (regex_compiled != NULL) {
    free(regex_compiled);
  }
}

void free_regex_array(regex_t *regex_array, int *regex_compiled,
                      int pattern_count) {
  for (int i = 0; i < pattern_count; i++) {
    if (regex_compiled != NULL && regex_compiled[i]) {
      regfree(&regex_array[i]);
    }
  }
}

int compile_regex(regex_t *regex, const char *pattern, int ignore_case) {
  int flags = REG_EXTENDED;
  int status = 0;

  if (ignore_case) {
    flags |= REG_ICASE;
  }

  status = regcomp(regex, pattern, flags);
  return status;
}

int match_line(const char *line, regex_t *regex, int invert_match) {
  regmatch_t match;
  int result = regexec(regex, line, 1, &match, 0);
  int matched = (result == 0) ? 1 : 0;

  if (invert_match) {
    matched = (matched == 0) ? 1 : 0;
  }

  return matched;
}

int match_any_pattern(const char *line, regex_t *regex_array,
                      int *regex_compiled, int pattern_count,
                      int invert_match) {
  int matched = 0;

  for (int i = 0; i < pattern_count && !matched; i++) {
    if (regex_compiled[i]) {
      matched = match_line(line, &regex_array[i], 0);
    }
  }

  if (invert_match) {
    matched = (matched == 0) ? 1 : 0;
  }

  return matched;
}

void print_match(const char *line, const char *filename, int line_num,
                 grep_flags *flags, int multiple_files, int match_count) {
  (void)match_count;

  if (flags->count_only || flags->files_with_match) {
    return;
  }

  if (multiple_files) {
    printf("%s:", filename);
  }

  if (flags->line_number) {
    printf("%d:", line_num);
  }

  printf("%s", line);
  if (line[strlen(line) - 1] != '\n') {
    printf("\n");
  }
}

void print_count(const char *filename, int count, int multiple_files) {
  if (multiple_files) {
    printf("%s:", filename);
  }
  printf("%d\n", count);
}
