#!/bin/bash

function applyAutopep8Format {
	find $1 \( -name "*.py" \) -exec autopep8 -i {} +
}

# Check if "autopep8" is installed
command -v autopep8 >/dev/null 2>&1 || { echo >&2 "\"autopep8\" is required but it's not installed.  Aborting."; exit 1; }
# Apply formatting
paths="../scripts/ "
for path in $paths; do
	applyAutopep8Format $path
done
