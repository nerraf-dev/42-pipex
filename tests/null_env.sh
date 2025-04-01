#!/bin/bash

# Test input and output files
input_file="input.txt"
output_file="output.txt"

# Create a sample input file
echo "Hello World!" > $input_file

# Run pipex with NULL environment
env -i ./pipex $input_file "grep Hello" "wc -l" $output_file
