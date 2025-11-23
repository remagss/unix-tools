#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

S21_CAT="./s21_cat"
SYS_CAT="cat"

TEST_FILES=(tests/test_files/*.txt)

FLAGS=(
    ""
    "-b"
    "-e"
    "-n"
    "-s"
    "-t"
    "-v"
    "-E"
    "-T"
    "-ben"
    "-set"
    "--number-nonblank"
    "--number"
    "--squeeze-blank"
)

echo "Running integration tests..."
PASSED=0
FAILED=0

for test_file in "${TEST_FILES[@]}"; do
    for flags in "${FLAGS[@]}"; do
        $S21_CAT $flags "$test_file" > s21_output.tmp 2>&1
        $SYS_CAT $flags "$test_file" > sys_output.tmp 2>&1
        
        if diff -q s21_output.tmp sys_output.tmp > /dev/null; then
            echo -e "${GREEN}✓ PASS${NC}: cat $flags $test_file"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC}: cat $flags $test_file"
            echo "Difference:"
            diff s21_output.tmp sys_output.tmp
            ((FAILED++))
        fi
        
        rm -f s21_output.tmp sys_output.tmp
    done
done

echo
echo "=== RESULTS ==="
echo -e "${GREEN}PASSED: $PASSED${NC}"
echo -e "${RED}FAILED: $FAILED${NC}"
echo "TOTAL: $((PASSED + FAILED))"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi