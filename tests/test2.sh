#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"


# test 2
echo
echo "Test 2: cat non_existent_file | wc -w"
# Run your program with a non-existent input file
"$PIPEX_PATH" non_existent_file "cat" "wc -w" output.txt


expected_output=$(cat non_existent_file | wc -w)
actual_output=$(cat output.txt)
if [ "$actual_output" == "$expected_output" ]; then
    echo -e "${GREEN}Test 2 passed${NC}"
else
    echo -e "${RED}Test 2 failed${NC}"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi
rm output.txt

