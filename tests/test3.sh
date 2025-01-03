#!/bin/bash

# This script tests the error handling of the pipex program when an invalid command is given as an argument.

#  Testing: < input.txt invalid_command | wc -w > output.txt
#  Testing: ./pipex input.txt invalid_command wc -w output.txt

# Expected error messages:
# 1. bash: invalid_command: command not found


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

# Run the standard bash command and capture the error output
bash_error_output=$( { < input.txt invalid_command | wc -w > output.txt; } 2>&1 )

# Run your program with an invalid command and capture the error output
pipex_error_output=$("$PIPEX_PATH" input.txt "invalid_command" "wc -w" output.txt 2>&1)

# Check if the output file was not created
if [ ! -f output.txt ]; then
    echo -e "${GREEN}Test 3 passed${NC}"
else
    echo -e "${RED}Test 3 failed${NC}"
    rm -f output.txt expected_output.txt error_output.txt
fi

# Check the error output
expected_error1="command not found"
expected_error2="open: No such file or directory"
if echo "$error_output" | grep -q "$expected_error1" && echo "$error_output" | grep -q "$expected_error2"; then
    echo -e "${GREEN}Error messages are correct${NC}"
else
    echo -e "${RED}Error messages are incorrect${NC}"
    echo "Expected error messages: $expected_error1, $expected_error2"
    echo "Actual error message: $error_output"
fi

# Compare bash and pipex error outputs
if [ "$bash_error_output" == "$error_output" ]; then
    echo -e "${GREEN}Bash and Pipex error outputs match${NC}"
else
    echo -e "${RED}Bash and Pipex error outputs do not match${NC}"
    echo "Bash error output: $bash_error_output"
    echo "Pipex error output: $error_output"
fi

# Clean up
rm -f input.txt
