#ifndef S21_GREP_H
#define S21_GREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SUCCESS 0
#define ERROR 1

typedef struct {
    int e;  // pattern (-e)
    int i;  // ignore uppercase vs lowercase (-i)
    int v;  // invert match (-v)
    int c;  // output count of matching lines only (-c)
    int l;  // output matching files only (-l)
    int n;  // precede each matching line with a line number (-n)
    // int h;  // output matching lines without preceding them by file names (-h)
    // int s;  // suppress error messages about nonexistent or unreadable files (-s)
    // int f;  // take regexes from a file (-f [file])
    // int o;  // output the matched parts of a matching line (-o)
} grep_flags;

#endif