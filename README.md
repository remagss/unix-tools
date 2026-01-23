# Implementation of 'cat' and 'grep'

Minimal reimplementation of Unix core utilities in C.
## 🛠️ Implemented Commands

### `cat` - File Concatenation
- Support of [all flags](#cat-options) (including GNU versions)
- Basic file output
- Support for multiple files
- Error handling
### `grep` - Pattern Matching
- Support of [all flags](#grep-options) including their _pair_ combinations
- Basic regex support
- File and stdin input
- Case-sensitive matching
## 🚀 Usage

### cat 

#### Build and usage
```bash
cd src/cat
make
./s21_cat [OPTION] [FILE]...
```
#### cat-options

| No. | Options                                                        | Description                                  |
| --- | -------------------------------------------------------------- | -------------------------------------------- |
| 1   | -b (GNU: --number-nonblank)                                    | numbers only non-empty lines                 |
| 2   | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $ |
| 3   | -n (GNU: --number)                                             | number all output lines                      |
| 4   | -s (GNU: --squeeze-blank)                                      | squeeze multiple adjacent blank lines        |
| 5   | -t implies -v (GNU: -T the same, but without implying -v)      | but also display tabs as ^I                  |
### grep
#### Build and usage
```bash
cd src/grep
make
./s21_grep [OPTION]... PATTERNS [FILE]...
```
#### grep-options

| No. | Options | Description                                                    |
| --- | ------- | -------------------------------------------------------------- |
| 1   | -e      | pattern                                                        |
| 2   | -i      | Ignore uppercase vs. lowercase.                                |
| 3   | -v      | Invert match.                                                  |
| 4   | -c      | Output count of matching lines only.                           |
| 5   | -l      | Output matching files only.                                    |
| 6   | -n      | Precede each matching line with a line number.                 |
## 🎓 Context

This project was done as part of the education at [School21](https://21-school.ru) 

**Internal info:**
Branch: C-1
Project: C2_SimpleBashUtils
Verter: 120%
