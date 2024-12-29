#!/bin/bash
# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"


# test 5:
echo
echo "Test 5: empty input file"
# Create an empty input file
touch input.txt

# Run your program with an empty input file
"$PIPEX_PATH" input.txt "cat" "wc -w" output.txt

# Check the output
expected_output="0"
actual_output=$(cat output.txt)

if [ "$actual_output" == "$expected_output" ]; then
    echo "Test 5 passed"
else
    echo "Test 5 failed"
    echo "Expected: $expected_output"
    echo "Got: $actual_output"
fi

# Clean up
rm input.txt output.txt
