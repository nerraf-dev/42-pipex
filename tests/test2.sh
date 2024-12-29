#!/bin/bash

# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Determine the absolute path to the pipex executable
PIPEX_PATH="$(cd "$(dirname "$0")/.." && pwd)/pipex"


# test 2
echo
echo "Test 2: cat non_existent_file | wc -w"
# Run your program with a non-existent input file
"$PIPEX_PATH" non_existent_file "cat" "wc -w" output.txt

# Check the output
if [ ! -f output.txt ]; then
    echo "Test 2 passed"
else
    echo "Test 2 failed"
    rm output.txt
fi
