#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

passed=0
failed=0
failed_tests=""

for test_script in tests/test*.sh; do
    output=$(bash "$test_script")
    echo "$output"
    if echo "$output" | grep -q "passed"; then
        passed=$((passed + 1))
    else
        failed=$((failed + 1))
        failed_tests+="$test_script \n"
        echo -e "${RED}Failed: $test_script${NC}"
    fi
done

echo
echo "Summary:"
echo -e "${GREEN}Passed: $passed${NC}"
echo -e "${RED}Failed: $failed${NC}"

if [ $failed -gt 0 ]; then
    echo -e "${RED}* $failed_tests${NC}"
fi
