# Solution explanation for AoC 2023 Day 21

## Part 1

** To be filled **

## Part 2

https://simontoth.substack.com/i/139980290/part-two

If you just read the problem description, it might seem completely intractable. That is, until you have a look at the input.

Our input is a square with some interesting properties. The row and column with our start are otherwise empty. The outside rows and columns are also empty. On top of that, all spaces that are 65 away from the start and from each corner are also empty (forming a neat diamond shape).

Now, consider which spaces will be reached in 65 and 65+131 steps.

![](part2_explanation.png "")

This is a suspiciously regular structure. If you investigate the requested number of steps, that number has the form q*131+65.

You could calculate the number of reachable spaces in each shape chunk, considering the odd/even pattern, which will form a checkerboard structure between tiles.

However, the structure is so regular that we can extrapolate the result if we calculate the values for 65+0*131, 65+1*131 and 65+2*131. We can use a tool like Wolfram Alpha to produce the quadratic formula expressing the number of reachable spaces.

The specific values will differ based on your input; ultimately, the result is just a formula.

```cpp
int64_t rounds = (steps - 65) / 131;
return 3814 + 15114 * rounds + 15024 * rounds * rounds;
```
