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

# Check if the directory contains a CMakeLists.txt file
if [ ! -f "$directory/CMakeLists.txt" ]; then
    echo "Directory does not contain a CMakeLists.txt file."
    exit 1
fi

# Change to the directory
cd "$directory" || exit 1

# Create a build directory
mkdir -p build

# Change to the build directory
cd build || exit 1

# Run CMake with N args entered as parameters
cmake "${@:2}" ..