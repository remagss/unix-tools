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
//   printf("Try './s21_cat --help' for more information.\n");
}
