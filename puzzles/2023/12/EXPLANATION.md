# Solution explanation for AoC 2023 Day 12

## Part 1

Solved it with two-dimensions DP.

First thing I need to do is to "expand" the contiguous groups of damaged springs to a boolean array, with true being "1 damaged" and false being " a gap of operational" (1 or more operational).

This means that 1,1,3 is expanded to [T, F, T, F, T, T, T]

Then I just have to match the characters to the array of booleans, which is very similar to most algos to match two strings together, for eg. Longest Common Subsequence.

```
dp[i][j] = how many arrangements when matching chars[i..n-1] with springs[j..m-1]
dp[i][j] = match(chars[i]):
  # => if(s[j] == T) dp[i+1][j+1] (you have to match one damaged spring)
       else 0
  . => if(s[j] == F) dp[i+1][j+1] + dp[i+1][j]  (you can either match the whole gap or match more operational inside the same gap)
       else 0
  ? => you can replace it to . or # so it's the sum of both
```

The tricky part now is the ends. Because you they can match either T or F (eg. ".#" and "#" match [T]). To handle the ends, I added '.' to the start and end of the chars and added 'F' to the springs. This way start and end always match.

## Part 2

** To be filled **
