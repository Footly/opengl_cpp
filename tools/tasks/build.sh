#!/bin/bash

# Check if directory parameter is provided
if [ -z "$1" ]; then
    echo "Please provide a directory as the first parameter."
    exit 1
fi

# Set the directory
directory="$1"

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Directory does not exist."
    exit 1
fi

# Check if the build directory exists
if [ ! -d "$directory/build" ]; then
    echo "Build directory does not exist."
    exit 1
fi

# Change to the build directory
cd "$directory/build" || exit 1

# Run make
make