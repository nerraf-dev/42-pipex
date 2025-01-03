#!/bin/bash

# This script tests the error handling of the pipex program when an invalid command is given as an argument.

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# Test 3: invalid_command
echo
echo "Test 3: invalid_command"
# Create input files
echo "Hello, World!" > input.txt

# Run the shell command
invalid_command < input.txt 2> expected_error.txt | wc -w > expected_output.txt


# Run the pipex command
"$PIPEX_PATH" input.txt "invalid_command" "wc -w" output.txt 2> error.txt

# Compare the outputs
if diff -q expected_output.txt output.txt && diff -q expected_error.txt error.txt; then
    echo -e "${GREEN}Test 3 passed!${NC}"
else
    echo -e "${RED}Test 3 failed!${NC}"
    echo "Differences in output:"
    cat expected_output.txt
    cat output.txt
    # diff expected_output.txt output.txt
    echo "Differences in error:"
    cat expected_error.txt
    cat error.txt
fi

# Clean up
# rm -f input.txt expected_output.txt output.txt expected_error.txt error.txt
