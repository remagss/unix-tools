#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep_flags flags = {0};
  int exit_code = SUCCESS;
  // int should_process_files = 1;

  int run_flag = run_grep(argc, argv, &flags);

  if (flags.show_help) {
    // show_help();
    // should_process_files = 0;
  } else if (run_flag != SUCCESS) {
    handle_error(run_flag, argv);
    exit_code = run_flag;
    // should_process_files = 0;
  }

  return exit_code;
}

int run_grep(int argc, char *argv[], grep_flags *flags) {
  int exit_code = SUCCESS;

  if (argc < 2) {
    exit_code = ERROR_INVALID_ARGS;
  } else {
    // exit_code = parse_flags(argc, argv, flags);
  }
  return exit_code;
}

int parse_flags(int argc, char *argv[], grep_flags *flags, char **pattern) {
  int status_flag = SUCCESS;
  int i = 1;
  int pattern_found = 0;

  while (i < argc && argv[i][0] == '-' && status_flag == SUCCESS) {
    if (argv[i][1] == '-') {
      status_flag = parse_gnu_flag(argv[i], flags);
    } else {
      status_flag = parse_short_flags(argv[i], flags, pattern, &pattern_found);
    }
    i++;
  }
  if (status_flag == SUCCESS && !pattern_found) {
    status_flag = handle_pattern(argc, argv, &i, pattern);
  }

  return (status_flag == SUCCESS) ? i : status_flag;
}

int parse_gnu_flag(char *arg, grep_flags *flags) {
  int status_flag = SUCCESS;
  if (strcmp(arg, "--help") == 0) {
    flags->show_help = 1;
  } else {
    status_flag = ERROR;
  }
  return status_flag;
}

int parse_short_flags(char *arg, grep_flags *flags, char **pattern,
                      int *pattern_found) {
  int status_flag = SUCCESS;
  int should_break = 0;

  for (int i = 1; arg[i] != '\0' && status_flag == SUCCESS; i++) {
    switch (arg[i]) {
      case 'e':
        flags->e = 1;
        status_flag = handle_e_flag(arg, i, flags, pattern, pattern_found);
        should_break = (status_flag == SUCCESS);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      // case 'h':
      //   flags->h = 1;
      //   break;
      // case 's':
      //   flags->s = 1;
      //   break;
      // case 'f':
      //   flags->f = 1;
      //   break;
      // case 'o':
      //   flags->o = 1;
      //   break;
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
  }
}
