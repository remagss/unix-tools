#include "s21_grep.h"

#include "s21_grep_flags.h"

int main(int argc, char *argv[]) {
  grep_flags flags = {0};
  int exit_code = SUCCESS;
  int should_process_files = 1;

  int status_flag = run_grep(argc, argv, &flags);

  if (status_flag != SUCCESS) {
    handle_error(status_flag, argv);
    exit_code = status_flag;
    should_process_files = 0;
  }

  if (should_process_files && flags.pattern_count > 0) {
    int file_count = count_files(argc, argv, &flags);
    int multiple_files = (file_count > 1) ? 1 : 0;

    for (int i = 1; i < argc; i++) {
      if (is_file_argument(argc, argv, i, &flags)) {
        process_file(argv[i], &flags, multiple_files);
      }
    }
  }

  return exit_code;
}

int run_grep(int argc, char *argv[], grep_flags *flags) {
  int exit_code = SUCCESS;

  if (argc < 2) {
    exit_code = ERROR_INVALID_ARGS;
  } else {
    exit_code = parse_flags(argc, argv, flags);
  }

  if (exit_code == SUCCESS && flags->pattern_count == 0) {
    exit_code = ERROR_INVALID_ARGS;
  }

  return exit_code;
}

int parse_flags(int argc, char *argv[], grep_flags *flags) {
  int status_flag = SUCCESS;
  int pattern_found = 0;
  int i = 1;

  while (i < argc && status_flag == SUCCESS) {
    if (argv[i][0] == '-') {
      status_flag =
          process_flag_argument(argc, argv, &i, flags, &pattern_found);
    } else if (!pattern_found) {
      add_pattern(flags, argv[i]);
      pattern_found = 1;
    }
    i++;
  }

  return status_flag;
}

int process_flag_argument(int argc, char *argv[], int *i, grep_flags *flags,
                          int *pattern_found) {
  int status_flag = SUCCESS;

  if (strcmp(argv[*i], "-e") == 0) {
    status_flag = process_e_flag(argc, argv, i, flags, pattern_found);
  } else {
    if (parse_short_flags(argv[*i], flags) != SUCCESS) {
      status_flag = ERROR_INVALID_FLAG;
    }
  }

  return status_flag;
}

int process_e_flag(int argc, char *argv[], int *i, grep_flags *flags,
                   int *pattern_found) {
  int status_flag = SUCCESS;

  if (*i + 1 < argc) {
    add_pattern(flags, argv[++(*i)]);
    *pattern_found = 1;
  } else {
    status_flag = ERROR_INVALID_FLAG;
  }

  return status_flag;
}

int parse_short_flags(char *arg, grep_flags *flags) {
  int status_flag = SUCCESS;

  for (int j = 1; arg[j] != '\0'; j++) {
    switch (arg[j]) {
      case 'i':
        flags->ignore_case = 1;
        break;
      case 'v':
        flags->invert_match = 1;
        break;
      case 'c':
        flags->count_only = 1;
        break;
      case 'l':
        flags->files_with_match = 1;
        break;
      case 'n':
        flags->line_number = 1;
        break;
      default:
        status_flag = ERROR_INVALID_FLAG;
    }
  }

  return status_flag;
}

void handle_error(int error_code, char *argv[]) {
  switch (error_code) {
    case ERROR:
      fprintf(stderr, "%s: unknown error\n", argv[0]);
      break;
    case ERROR_INVALID_ARGS:
      fprintf(stderr, "%s: invalid arguments\n", argv[0]);
      break;
    case ERROR_FILE_OPEN:
      fprintf(stderr, "%s: No such file or directory\n", argv[0]);
      break;
    case ERROR_INVALID_FLAG:
      fprintf(stderr, "%s: invalid option\n", argv[0]);
      break;
    case ERROR_REGEX_COMPILE:
      fprintf(stderr, "%s: regex compilation error\n", argv[0]);
      break;
  }
}
