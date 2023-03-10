#!/bin/bash

function applyClangFormat {
	find $1 \( -name "*.cpp" -or -name "*.h" -or -name "*.hpp"\) -exec clang-format -style=file -i {} +
}

# utils folder
utilsPaths = "../utils/src ../utils/src/geometry2d ../utils/include ../utils/include/geometry2d "
for path in $utilsPaths; do
	applyClangFormat $path
done

# puzzles folder
puzzlesPaths = "../puzzles/2021/1/sources ../puzzles/2022/1/sources "
for path in $puzzlesPaths; do
	applyClangFormat $path
done
