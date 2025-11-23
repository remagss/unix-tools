#include "s21_cat_flags.h"

void process_file_with_flags(FILE *file, cat_flags *flags) {
  int ch;
  int line_number = 1;
  int prev_ch = '\n';
  int empty_line_count = 0;

  while ((ch = fgetc(file)) != EOF) {
    int result =
        process_character(ch, flags, &line_number, &prev_ch, &empty_line_count);
    if (result != -1) {
      putchar(result);
    }
  }
}

int process_character(int ch, cat_flags *flags, int *line_number, int *prev_ch,
                      int *empty_line_count) {
  int should_print = 1;
  int processed_char = ch;

  handle_numbering(flags, ch, line_number, prev_ch);

  should_print = handle_squeeze_blank(flags, ch, prev_ch, empty_line_count);

  if (should_print) {
    processed_char = handle_nonprinting(ch, flags);
    if (processed_char == -1) {
      should_print = 0;
    }
  }

  *prev_ch = ch;
  return should_print ? processed_char : -1;
}

void handle_numbering(cat_flags *flags, int ch, int *line_number,
                      int *prev_ch) {
  if (flags->number && *prev_ch == '\n') {
    printf("%6d\t", (*line_number)++);
  }

  if (flags->number_nonblank && *prev_ch == '\n' && ch != '\n') {
    printf("%6d\t", (*line_number)++);
  }
}

int handle_squeeze_blank(cat_flags *flags, int ch, int *prev_ch,
                         int *empty_line_count) {
  int should_print = 1;

  if (flags->squeeze_blank) {
    if (ch == '\n' && *prev_ch == '\n') {
      (*empty_line_count)++;
      if (*empty_line_count > 1) {
        should_print = 0;
      }
    } else {
      *empty_line_count = 0;
    }
  }

  return should_print;
}

int handle_nonprinting(int ch, cat_flags *flags) {
  if (ch == EOF) {
    return ch;
  }

  unsigned char uc = (unsigned char)ch;

  if (uc == '\n' && flags->show_ends) {
    printf("$");
  }

  if (uc == '\t' && flags->show_tabs) {
    printf("^I");
    return -1;
  }

  if (flags->show_nonprinting) {
    if (uc < 32 && uc != 9 && uc != 10) {
      printf("^%c", uc + 64);
      return -1;
    } else if (uc == 127) {
      printf("^?");
      return -1;
    }
  }

  return ch;
}