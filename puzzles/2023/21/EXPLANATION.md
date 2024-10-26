# Solution explanation for AoC 2023 Day 21

## Part 1

** To be filled **

## Part 2

https://simontoth.substack.com/i/139980290/part-two

If you just read the problem description, it might seem completely intractable. That is, until you have a look at the input.

Our input is a square with some interesting properties. The row and column with our start are otherwise empty. The outside rows and columns are also empty. On top of that, all spaces that are 65 away from the start and from each corner are also empty (forming a neat diamond shape).

Now, consider which spaces will be reached in 65 and 65+131 steps.

![](part2_explanation.png)

This is a suspiciously regular structure. If you investigate the requested number of steps, that number has the form q*131+65.

You could calculate the number of reachable spaces in each shape chunk, considering the odd/even pattern, which will form a checkerboard structure between tiles.

However, the structure is so regular that we can extrapolate the result if we calculate the values for 65+0*131, 65+1*131 and 65+2*131. We can use a tool like Wolfram Alpha to produce the quadratic formula expressing the number of reachable spaces.

The specific values will differ based on your input; ultimately, the result is just a formula.

Explatation 2:

The periodicity of the grid/map can be emulated simply by `grid[i % size][j % size]`, where `size = 131` is the width and height of the grid.In practice though, the number of steps is too high for this. But, unlike the example input, the full input is rigged. If you visualize the entire map (open in text editor and make the font size very small), you will notice a big diamond shape of free path. It turns out that the entire perimeter of this diamond is exactly reached after `size//2 = 65` steps. Because the corner of the diamond are at the boundary of the map (when thought of as non-periodic), and the middle row and column (where the starting position `S` is located) are completely free (no rocks `#`), we are then guaranteed that another `8` surrounding diamonds will be exactly reached after `size = 131` steps (in addition to the first `size//2 = 65` steps). After another `size = 131` steps, the next layer of diamonds are exactly reached, and so on. If we were in the continuous limit and with no rocks `#`, the number of positions covered as a function of steps would be `A(t) = πt²` (area of disk), where t is the number of steps. Having discrete steps and dismissing certain positions (adding in rocks) cannot introduce higher-order terms, so the most general form will be `A(t) = at² + bt + c`.  We can determine `a`, `b` and `c` if we know `A(t)` for three values of `t`. Here we can use `t = size//2 = 65`, `t = size//2 + size = 196` and `t = size//2 + 2*size = 327`, as argued above. One way of doing this in practice (obtaining `A(t)` without actually ever finding `a`, `b` and `c`) is through the [Lagrange interpolation polynomial](https://en.wikipedia.org/wiki/Lagrange_polynomial). The final answer is then `A(26501365)`. Note that our formula `A(t)` is only valid for `t` of the form `t = size//2 + n*size = 65 + n*131`, which is exactly the form of the requested step number `26501365 = 65 + 202300*131`).
