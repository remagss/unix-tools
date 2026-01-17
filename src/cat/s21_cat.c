#include "s21_cat.h"

#include "s21_cat_flags.h"

int main(int argc, char *argv[]) {
  cat_flags flags = {0};
  int exit_code = SUCCESS;
  int should_process_files = 1;

  int status_flag = run_cat(argc, argv, &flags);

  if (flags.show_help) {
    show_help();
    should_process_files = 0;
  }

  if (should_process_files) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        print_file_content(argv[i], &flags);
      }
    }
  }

  if (status_flag != SUCCESS) {
    handle_error(status_flag, argv);
    exit_code = status_flag;
  }

  return exit_code;
}

int run_cat(int argc, char *argv[], cat_flags *flags) {
  int exit_code = SUCCESS;

  if (argc < 2) {
    exit_code = ERROR_INVALID_ARGS;
  } else {
    exit_code = parse_flags(argc, argv, flags);
  }
  return exit_code;
}

int parse_flags(int argc, char *argv[], cat_flags *flags) {
  int status_flag = SUCCESS;

  for (int i = 1; i < argc && status_flag == SUCCESS; i++) {
    if (argv[i][0] == '-') {
      status_flag = process_flag_in_parse(argv[i], flags);
    }
  }

  if (flags->number_nonblank) {
    flags->number = 0;  // Disabled flag -n if -b is active
  }

  return status_flag;
}

int process_flag_in_parse(char *arg, cat_flags *flags) {
  int status_flag = SUCCESS;

  if (arg[1] == '-') {
    if (parse_gnu_flags(arg, flags) != SUCCESS) {
      status_flag = ERROR_INVALID_GNU_FLAG;
    }
  } else {
    if (parse_short_flags(arg, flags) != SUCCESS) {
      status_flag = ERROR_INVALID_SHORT_FLAG;
    }
  }

  return status_flag;
}

int parse_gnu_flags(char *arg, cat_flags *flags) {
  int status_flag = SUCCESS;
  if (strcmp(arg, "--number-nonblank") == 0) {
    flags->number_nonblank = 1;
  } else if (strcmp(arg, "--number") == 0) {
    flags->number = 1;
  } else if (strcmp(arg, "--squeeze-blank") == 0) {
    flags->squeeze_blank = 1;
  } else if (strcmp(arg, "--help") == 0) {
    flags->show_help = 1;
  } else {
    status_flag = ERROR;
  }

  return status_flag;
}

int parse_short_flags(char *arg, cat_flags *flags) {
  int status_flag = SUCCESS;

  for (int j = 1; arg[j] != '\0'; j++) {
    switch (arg[j]) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'e':
        flags->show_ends = 1;
        flags->show_nonprinting = 1;  // implies -v
        break;
      case 'n':
        flags->number = 1;
        break;
      case 's':
        flags->squeeze_blank = 1;
        break;
      case 't':
        flags->show_tabs = 1;
        flags->show_nonprinting = 1;  // implies -v
        break;
      case 'v':
        flags->show_nonprinting = 1;
        break;

      case 'E':
        flags->show_ends = 1;
        break;
      case 'T':
        flags->show_tabs = 1;
        break;
      default:
        status_flag = ERROR;
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
    case ERROR_INVALID_SHORT_FLAG:
      fprintf(stderr, "%s: invalid option\n", argv[0]);
      break;
    case ERROR_INVALID_GNU_FLAG:
      fprintf(stderr, "%s: invalid GNU option\n", argv[0]);
      break;
  }
  printf("Try './s21_cat --help' for more information.\n");
}

int print_file_content(const char *filename, cat_flags *flags) {
  int status_flag = SUCCESS;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    status_flag = ERROR_FILE_OPEN;
  } else {
    process_file_with_flags(file, flags);
    fclose(file);
  }
  return status_flag;
}

void show_help() {
  printf("Usage: ./s21_cat [OPTION]... [FILE]...\n");
  printf("Concatenate FILE(s) to standard output.\n\n");

  printf(
      "  -b, --number-nonblank    number nonempty output lines, overrides "
      "-n\n");
  printf("  -e                       equivalent to -vE\n");
  printf("  -E, --show-ends          display $ at end of each line\n");
  printf("  -n, --number             number all output lines\n");
  printf("  -s, --squeeze-blank      suppress repeated empty output lines\n");
  printf("  -t                       equivalent to -vT\n");
  printf("  -T, --show-tabs          display TAB characters as ^I\n");
  printf(
      "  -v, --show-nonprinting   use ^ and M- notation, except for LFD and "
      "TAB\n");
  printf("      --help               display this help and exit\n\n");

  printf("Examples:\n");
  printf(
      "  s21_cat f - g  Output f's contents, then standard input, then g's "
      "contents.\n");
  printf("  s21_cat        Copy standard input to standard output.\n\n\n");

  printf("cat implementation for School 21.\n\n");
  printf("With love,\n");
  printf("merlewhi/remagss\n");
}