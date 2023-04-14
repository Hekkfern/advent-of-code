# Solution explanation for AoC 2022 Day 2

To optimize performance, [Look-Up Tables](https://en.wikipedia.org/wiki/Lookup_table) (LUTs) have been manually created for all possible combinations of inputs. This task is feasible for any developer since the number of combinations is relatively small. By using a LUT, data retrieval time is significantly faster, with a constant access time of O(1) regardless of the size of the input data.

As a result, the solution relies on efficiently reading data from the appropriate LUTs, which significantly speeds up the puzzle-solving process.

## Part 1

For Part 1, a LUT called `PointsPerShapes` has been created which links a pair with the opponent's shape as well as yours, and it returns the total number of points for this combination.
Then, all the points for every round is accumulated.

## Part 2

For Part 2, another LUT called `ResultConversion` has been created which links a pair with the desired match result and the opponent's shape, and it returns the shape you should use. Then, the result of this LUT is used in the LUT created in Part 1 to get the total number of points for the round.
Then, all the points for every round is accumulated.
