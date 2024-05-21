#!/bin/bash

echo "Running configure task..."

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

# Change to the directory
cd "$directory" || exit 1

# Remove the build directory
rm -rf build

echo "Build directory cleaned."