# Solution explanation for AoC 2023 Day 19

## Part 1

** To be filled **

## Part 2

There's basically 3 things we need to care about when filtering a range. If the range is fully inside the filter, partially, or not at all.

If it's fully inside, we just accept/reject/pass to next filter the whole range.

If it's partially inside, we split the range at the compare value into 2 ranges. Accept/reject/pass the range that's inside the compare. Put the range that's outside the compare back into the queue with the same filter.

If the range is outside the compare completely, move onto the next instruction in the filter.

If we get to the last instruction in a filter, accept/reject/pass to next filter the range.

Upon accepting a range, we multiply the range values and add to total.
