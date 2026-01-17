# Тесты для s21_grep

## Структура тестов

- `test_files/` - папка с тестовыми файлами
- `run_integration_tests.sh` - автоматические интеграционные тесты
- `manual_test.sh` - ручные тесты для демонстрации функциональности

## Тестовые файлы

1. **basic.txt** - базовый файл с различными паттернами для поиска
2. **empty_lines.txt** - файл с пустыми строками
3. **long_line.txt** - файл с очень длинными строками
4. **ascii_chars.txt** - файл со специальными символами
5. **empty_file.txt** - пустой файл
6. **multiple_patterns.txt** - файл с несколькими паттернами
7. **numbers.txt** - файл с числами

## Запуск тестов

### Ручные тесты (для просмотра работы программы):
```bash
cd src/grep
./tests/manual_test.sh
```

### Автоматические интеграционные тесты:
```bash
cd src/grep
make test
# или
./tests/run_integration_tests.sh
```

## Примеры использования

### Базовый поиск:
```bash
./s21_grep "test" tests/test_files/basic.txt
```

### Поиск с номерами строк:
```bash
./s21_grep -n "test" tests/test_files/basic.txt
```

### Поиск без учета регистра:
```bash
./s21_grep -i "TEST" tests/test_files/basic.txt
```

### Инвертированный поиск:
```bash
./s21_grep -v "test" tests/test_files/basic.txt
```

### Подсчет совпадений:
```bash
./s21_grep -c "test" tests/test_files/basic.txt
```

### Список файлов с совпадениями:
```bash
./s21_grep -l "test" tests/test_files/basic.txt tests/test_files/empty_lines.txt
```

### Несколько файлов:
```bash
./s21_grep "test" tests/test_files/basic.txt tests/test_files/empty_lines.txt
```

### Несколько паттернов:
```bash
./s21_grep -e "test" -e "line" tests/test_files/basic.txt
```

### Комбинированные флаги:
```bash
./s21_grep -n -i "TEST" tests/test_files/basic.txt
```
