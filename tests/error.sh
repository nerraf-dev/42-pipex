#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# Test 6: < input grep Hello | wc -l > output
echo
echo "Test 6: < input grep Hello | wc -l > output"

# Ensure input.txt does not exist
rm -f input.txt

# Run your program with a non-existent input file
"$PIPEX_PATH" input.txt "grep Hello" "wc -l" output.txt

# Check the output
expected_output="0"
actual_output=$(cat output.txt)

if [ "$actual_output" == "$expected_output" ]; then
    echo -e "${GREEN}Test 6 passed${NC}"
else
    echo -e "${RED}Test 6 failed${NC}"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi

# Clean up
rm -f output.txt
