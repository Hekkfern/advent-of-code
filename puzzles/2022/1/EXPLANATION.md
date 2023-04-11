# AoC 2022 Day 1: Calorie Counting

## Part 1

The input file is read line by line, and each line is used before moving on to the next one. This approach reduces the number of iterations required to process the lines of the file, as compared to reading the entire file and then iterating over the parsed values.

If a non-empty line is encountered (i.e., a line with a numeric value), its value is added to the accumulator.

When an empty line is encountered, it signifies the end of a group of numbers, namely the list of calories for a particular elf. At this point, we stop accumulating and check if the current accumulated value is the maximum seen so far. If it is, we update the maximum value accordingly. We then reset the accumulator to zero and proceed to accumulate calories for the next elf, checking at each stage if the new value is higher than the current maximum.

## Part 2

The input file is once again read line by line.

Our objective remains to find the maximum number of calories. However, this time, we maintain a record of the three highest values we have encountered so far. We update this ranking whenever a new value is found that surpasses any of the three current highest values.

After checking all the elves, the sum of the three highest values is calculated.
