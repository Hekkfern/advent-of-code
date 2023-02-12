Let's see if I can explain why mod LCM works :book: :
From the worry level we only need to:
- add n / multiply by n / square it
- check divisibility by known divisors
  Divisibility by d is usually done with % d == 0
  If we only had 1 divisor d to check, it would be simple:
  just keep the worry level in [0..d-1] by doing % d (math: also known as Z/dZ).
  Believe that addition and multiplication will behave (math: Z/dZ is a ring).
  Then divisibility is just  == 0
  What if we have 2 divisors d1 and d2 ?
  We could keep 2 worry levels [0..d1-1] and [0..d2-1]
  But can we figure out a range [0..D-1] that will work for both?
  Let's try with 2 and 3. if we display the result of the mod we get:
  N  : 0,1,2,3,4,5,6,7,8,9...
  N%2: 0,1,0,1,0,1,0,1,0,1...
  N%3: 0,1,2,0,1,2,0,1,2,0...
  We can't choose D=2 as it only has 2 numbers and %3 needs 3 different values.
  Does D=3 work ? Let's try it
  N    : 0,1,2, 3,4,5, 6,7,8, 9...
  N%3  : 0,1,2, 0,1,2, 0,1,2, 0...

N%3%2: 0,1,0, 0,1,0, 0,1,0, 0...
N%3%3: 0,1,2, 0,1,2, 0,1,2, 0...
What happened ? our %2 is wrong (3%2 is not 0), we broke the pattern (literally we made 0+1=0)
Why ? Because we cut in the middle of the 0,1 loop.
Where can we cut our number line without breaking the %2 and %3 pattern ?
We can look at the combined pattern of both lines together.
We started at (0,0) so we should cut just before repeating (0,0), which is at 6:
N  : 0,1,2,3,4,5, 6,7,8,9...
N%2: 0,1,0,1,0,1, 0,1,0,1...
N%3: 0,1,2,0,1,2, 0,1,2,0...
We need a loop of 6 in order to not break inner loops of 2 and 3.
Said differently: the pattern of 0,1 and the pattern of 0,1,2 must fit completely in it.
6 is not the only number that works, 12 would too; in fact, any common multiple of 2 and 3 will do the job (because the 0 will align, i.e. both mods are 0). LCM is just the smallest.
I let you generalize to 3+ numbers (and numbers than aren't prime).