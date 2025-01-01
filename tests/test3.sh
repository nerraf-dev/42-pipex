#!/bin/bash

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

# Run your program with an invalid command and capture the error output
error_output=$("$PIPEX_PATH" input.txt "invalid_command" "wc -w" output.txt 2>&1)

# Check if the output file was not created
if [ ! -f output.txt ]; then
    echo -e "${GREEN}Test 3 passed${NC}"
else
    echo -e "${RED}Test 3 failed${NC}"
    rm -f output.txt
fi

# Check for expected error messages
expected_error1="command not found"
expected_error2="open: No such file or directory"
if echo "$error_output" | grep -q "$expected_error1" && echo "$error_output" | grep -q "$expected_error2"; then
    echo -e "${GREEN}Error messages are correct${NC}"
else
    echo -e "${RED}Error messages are incorrect${NC}"
    echo "Expected error messages: $expected_error1, $expected_error2"
    echo "Actual error message: $error_output"
fi

# Clean up
rm -f input.txt
