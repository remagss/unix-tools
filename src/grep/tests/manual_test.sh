#!/bin/bash

# Simple manual test script to demonstrate s21_grep functionality

GREP="./s21_grep"
TEST_DIR="tests/test_files"

echo "=== Manual Tests for s21_grep ==="
echo

echo "1. Basic search:"
echo "Command: $GREP \"test\" $TEST_DIR/basic.txt"
$GREP "test" $TEST_DIR/basic.txt
echo

echo "2. Search with line numbers (-n):"
echo "Command: $GREP -n \"test\" $TEST_DIR/basic.txt"
$GREP -n "test" $TEST_DIR/basic.txt
echo

echo "3. Case insensitive search (-i):"
echo "Command: $GREP -i \"TEST\" $TEST_DIR/basic.txt"
$GREP -i "TEST" $TEST_DIR/basic.txt
echo

echo "4. Invert match (-v):"
echo "Command: $GREP -v \"test\" $TEST_DIR/basic.txt"
$GREP -v "test" $TEST_DIR/basic.txt
echo

echo "5. Count matches (-c):"
echo "Command: $GREP -c \"test\" $TEST_DIR/basic.txt"
$GREP -c "test" $TEST_DIR/basic.txt
echo

echo "6. List files with matches (-l):"
echo "Command: $GREP -l \"test\" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt"
$GREP -l "test" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt
echo

echo "7. Multiple files:"
echo "Command: $GREP \"test\" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt"
$GREP "test" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt
echo

echo "8. Multiple files with line numbers:"
echo "Command: $GREP -n \"test\" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt"
$GREP -n "test" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt
echo

echo "9. Pattern with -e flag:"
echo "Command: $GREP -e \"test\" -e \"line\" $TEST_DIR/basic.txt"
$GREP -e "test" -e "line" $TEST_DIR/basic.txt
echo

echo "10. Combined flags (-n -i):"
echo "Command: $GREP -n -i \"TEST\" $TEST_DIR/basic.txt"
$GREP -n -i "TEST" $TEST_DIR/basic.txt
echo

echo "11. Count with multiple files:"
echo "Command: $GREP -c \"test\" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt"
$GREP -c "test" $TEST_DIR/basic.txt $TEST_DIR/empty_lines.txt
echo

echo "12. Long line test:"
echo "Command: $GREP \"test\" $TEST_DIR/long_line.txt"
$GREP "test" $TEST_DIR/long_line.txt
echo

echo "=== All manual tests completed ==="
