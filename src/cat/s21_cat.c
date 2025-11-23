#include "s21_cat.h"

int main(int argc, char *argv[]) {
    cat_flags flags = {0};
    
    int run_flag = run_cat(argc, argv, &flags);

    // printf("Parsed flags: b=%d, e=%d, n=%d, s=%d, t=%d, v=%d\n", // Debug function
    //        flags.number_nonblank, flags.show_ends, flags.number,
    //        flags.squeeze_blank, flags.show_tabs, flags.show_nonprinting);
        
    if (run_flag != 0) {
        handle_error(run_flag, argv);
    } else {
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-') {
                print_file_content(argv[i], &flags);
            }
        }
    }

    return run_flag;
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
    int error_flag = SUCCESS;

    for (int i = 1; i < argc && error_flag == SUCCESS; i++) { 
        if (argv[i][0] != '-') continue;

        if (argv[i][1] == '-') {
            if (parse_gnu_flags(argv[i], flags) != SUCCESS) {
                error_flag = ERROR_INVALID_GNU_FLAG;
            }
        } else {
            if (parse_short_flags(argv[i], flags) != SUCCESS) {
                error_flag = ERROR_INVALID_SHORT_FLAG;
            }
        }
    }
    
    if (flags->number_nonblank) {
        flags->number = 0; // Disabled flag -n if -b is active 
    }

    return error_flag;
}

int parse_gnu_flags(char *arg, cat_flags *flags) {
    int error_flag = SUCCESS;
    if (strcmp(arg, "--number-nonblank") == 0) {
        flags->number_nonblank = 1;
    } else if (strcmp(arg, "--number") == 0) {
        flags->number = 1;
    } else if (strcmp(arg, "--squeeze-blank") == 0) {
        flags->squeeze_blank = 1;
    } else {
       error_flag = ERROR; 
    }
    
    return error_flag;
}

int parse_short_flags(char *arg, cat_flags *flags) {
    int error_flag = SUCCESS;

    for (int j = 1; arg[j] != '\0'; j++) {
        switch (arg[j]) {
            case 'b': 
                flags->number_nonblank = 1; 
                break;
            case 'e': 
                flags->show_ends = 1;
                flags->show_nonprinting = 1; // implies -v
                break;
            case 'n': 
                flags->number = 1;
                break;
            case 's':
                flags->squeeze_blank = 1;
                break;
            case 't':
                flags->show_tabs = 1;
                flags->show_nonprinting = 1; // implies -v
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
                error_flag = ERROR;
        }
    }

    return error_flag;
}


void print_file_content(const char *filename, cat_flags *flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return;
    }
    
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    
    fclose(file);
}

void handle_error(int error_code, char *argv[]) {
    switch(error_code) {
        case ERROR:
            fprintf(stderr, "%s: unknown error\n", argv[0]);
            break;
        case ERROR_INVALID_ARGS:
            fprintf(stderr, "%s: invalid arguments\n", argv[0]);
            break;
        case ERROR_INVALID_SHORT_FLAG:
            fprintf(stderr, "%s: invalid option\n", argv[0]);
            break;
        case ERROR_INVALID_GNU_FLAG:
            fprintf(stderr, "%s: invalid GNU option\n", argv[0]);
            break;
        case ERROR_FILE_OPEN:
            fprintf(stderr, "%s: No such file or directory\n", argv[0]);
            break;
    }
}