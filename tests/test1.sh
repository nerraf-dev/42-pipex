#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"

# Create input files
echo "Hello, World!" > input.txt

# Run your program
"$PIPEX_PATH" input.txt "cat" "wc -w" output.txt

# Check the output
expected_output="2"
actual_output=$(cat output.txt)
echo "Test 1: cat input.txt | wc -w"
if [ "$actual_output" == "$expected_output" ]; then
    echo "Test 1 passed"
else
    echo "Test 1 failed"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi

# Clean up
rm input.txt output.txt

