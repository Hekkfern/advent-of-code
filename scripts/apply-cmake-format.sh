#!/bin/bash

function applyCMakeFormat {
	find $1 \( -name "*.cmake" -or -name "CMakeLists.txt" \) -exec cmake-format -i {} +
}

# Check if "cmake-format" is installed
command -v cmake-format >/dev/null 2>&1 || { echo >&2 "\"cmake-format\" is required but it's not installed.  Aborting."; exit 1; }
# Apply formatting
paths="../utils/ ../puzzles/ ../cmake/ "
for path in $paths; do
	applyCMakeFormat $path
done
