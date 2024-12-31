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

# Run your program with an invalid command
"$PIPEX_PATH" input.txt "invalid_command" "wc -w" output.txt

# Check the output
if [ ! -f output.txt ]; then
    echo -e "${GREEN}Test 3 passed${NC}"
else
    echo -e "${RED}Test 3 failed${NC}"
    rm output.txt
fi

# Clean up
# rm input.txt
