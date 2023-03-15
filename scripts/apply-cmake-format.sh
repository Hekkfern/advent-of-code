#!/bin/bash

function applyCMakeFormat {
	find $1 \( -name "*.cmake" -or -name "CMakeLists.txt" \) -exec cmake-format -i {} +
}

paths="../utils/ ../puzzles/ ../cmake/ "
for path in $paths; do
	applyCMakeFormat $path
done
