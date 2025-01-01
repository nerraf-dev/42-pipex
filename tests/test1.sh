#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# Print the PIPEX_PATH for debugging
# echo "PIPEX_PATH: $PIPEX_PATH"

# Create input files
echo "Hello, World!" > input.txt

# Print the current directory and list files for debugging
# echo "Current directory: $(pwd)"
# ls -l

# Run your program
"$PIPEX_PATH" input.txt "cat" "wc -w" output.txt

# Check the output
expected_output=$(cat input.txt | wc -w)
actual_output=$(cat output.txt)
echo "Test 1: cat input.txt | wc -w"
if [ "$actual_output" == "$expected_output" ]; then
    echo -e "${GREEN}Test 1 passed${NC}"
else
    echo -e "${RED}Test 1 failed${NC}"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi

# Clean up
rm input.txt output.txt
