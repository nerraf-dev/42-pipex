#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# test 4:
echo
echo "Test 4: cat input.txt | grep Hello"
# Create input files
echo "Hello, World!" > input.txt

# Run your program with multiple commands
"$PIPEX_PATH" input.txt "cat" "grep Hello" output.txt

# Check the output
expected_output="Hello, World!"
actual_output=$(cat output.txt)

if [ "$actual_output" == "$expected_output" ]; then
    echo -e "${GREEN}Test 4 passed!${NC}"
else
    echo "Test 4 failed"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi

# Clean up
rm input.txt output.txt
