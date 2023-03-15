#!/bin/bash

function applyClangFormat {
	find $1 \( -name "*.cpp" -or -name "*.h" -or -name "*.hpp" \) -exec clang-format -style=file -i {} +
}

# Check if "clang-format" is installed
command -v clang-format >/dev/null 2>&1 || { echo >&2 "\"clang-format\" is required but it's not installed.  Aborting."; exit 1; }
# Apply formatting
paths="../utils/ ../puzzles/ "
for path in $paths; do
	applyClangFormat $path
done
