#!/bin/bash

function applyClangFormat {
	find $1 \( -name "*.cpp" -or -name "*.h" -or -name "*.hpp" \) -exec clang-format -style=file -i {} +
}

paths="../utils/ ../puzzles/ "
for path in $utilsPaths; do
	applyClangFormat $path
done
