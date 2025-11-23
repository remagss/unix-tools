#include "s21_cat_output.h"

void process_file_with_flags(FILE *file, cat_flags *flags) {
    int ch;
    int line_number = 1; // for line numbering (-n, -b)
    int prev_ch = '\n'; // for detect new line
    int empty_line_count = 0; // (-s)
    
    while ((ch = fgetc(file)) != EOF) {
        int should_print = process_character(ch, flags, &line_number, &prev_ch, &empty_line_count);
        if (should_print) {
            putchar(ch);
        }
    }
}

int process_character(int ch, cat_flags *flags, int *line_number, int *prev_ch, int *empty_line_count) {
    int should_print = 1;
    
    handle_numbering(flags, ch, line_number, prev_ch);
    
    should_print = handle_squeeze_blank(flags, ch, prev_ch, empty_line_count);
    
    if (should_print) {
        ch = handle_nonprinting(ch, flags);
    }
    
    *prev_ch = ch;
    return should_print;
}

