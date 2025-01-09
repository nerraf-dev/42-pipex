#!/bin/bash

# This script tests the error handling of the pipex program when an invalid command is given as an argument.

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# Test: invalid_command
echo
echo "Test: invalid_command"
# Create input files
echo "Hello, World!" > input.txt

# Run the shell command
no-cmd < input.txt 2> expected_error.txt | wc -w > expected_output.txt
expected_status=$?

# Run the pipex command
"$PIPEX_PATH" input.txt "no-cmd" "wc -w" output.txt 2> error.txt
pipex_status=$?

# Compare the outputs
if diff -q expected_output.txt output.txt && tail -n +2 expected_error.txt | diff -q - <(tail -n +2 error.txt) && [ $expected_status -eq $pipex_status ]; then
    echo -e "${GREEN}Test passed!${NC}"
else
    echo -e "${RED}Test failed!${NC}"
    echo "Differences in output:"
    cat expected_output.txt
    cat output.txt
    echo "Differences in error:"
    cat expected_error.txt
    cat error.txt
    echo "Expected exit status: $expected_status"
    echo "Pipex exit status: $pipex_status"
fi

# Clean up
rm -f input.txt expected_output.txt output.txt expected_error.txt error.txt
