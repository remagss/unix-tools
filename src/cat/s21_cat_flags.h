#ifndef S21_CAT_FLAGS_H
#define S21_CAT_FLAGS_H

#include "s21_cat.h"

void process_file_with_flags(FILE *file, cat_flags *flags);
int process_character(int ch, cat_flags *flags, int *line_number, int *prev_ch, int *empty_line_count);
void handle_numbering(cat_flags *flags, int ch, int *line_number, int *prev_ch);
int handle_squeeze_blank(cat_flags *flags, int ch, int *prev_ch, int *empty_line_count);
int handle_nonprinting(int ch, cat_flags *flags);

#endif