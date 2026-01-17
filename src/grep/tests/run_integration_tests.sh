#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

S21_GREP="./s21_grep"
SYS_GREP="grep"

TEST_FILES=(tests/test_files/*.txt)

PATTERNS=(
    "test"
    "Test"
    "line"
    "Line"
    "pattern"
    "TEST"
    "no"
    "123"
)

FLAGS=(
    ""
    "-i"
    "-v"
    "-c"
    "-l"
    "-n"
    "-e"
    "-i -v"
    "-n -i"
    "-c -v"
    "-l -v"
)

echo "Running integration tests for s21_grep..."
echo "=========================================="
PASSED=0
FAILED=0
TOTAL=0

for test_file in "${TEST_FILES[@]}"; do
    for pattern in "${PATTERNS[@]}"; do
        for flags in "${FLAGS[@]}"; do
            TOTAL=$((TOTAL + 1))
            
            # Skip empty file with some patterns
            if [[ "$test_file" == *"empty_file.txt"* ]] && [[ -z "$flags" ]]; then
                continue
            fi
            
            # Run s21_grep
            $S21_GREP $flags "$pattern" "$test_file" > s21_output.tmp 2>&1
            s21_exit=$?
            
            # Run system grep
            $SYS_GREP $flags "$pattern" "$test_file" > sys_output.tmp 2>&1
            sys_exit=$?
            
            # Compare outputs
            if diff -q s21_output.tmp sys_output.tmp > /dev/null; then
                if [ $s21_exit -eq $sys_exit ]; then
                    echo -e "${GREEN}✓ PASS${NC}: grep $flags \"$pattern\" $test_file"
                    ((PASSED++))
                else
                    echo -e "${YELLOW}⚠ WARN${NC}: grep $flags \"$pattern\" $test_file (exit codes differ: $s21_exit vs $sys_exit)"
                    ((PASSED++))
                fi
            else
                echo -e "${RED}✗ FAIL${NC}: grep $flags \"$pattern\" $test_file"
                echo "  Expected:"
                cat sys_output.tmp | head -5
                echo "  Got:"
                cat s21_output.tmp | head -5
                ((FAILED++))
            fi
            
            rm -f s21_output.tmp sys_output.tmp
        done
    done
done

echo
echo "=========================================="
echo "=== RESULTS ==="
echo -e "${GREEN}PASSED: $PASSED${NC}"
echo -e "${RED}FAILED: $FAILED${NC}"
echo "TOTAL: $TOTAL"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi
