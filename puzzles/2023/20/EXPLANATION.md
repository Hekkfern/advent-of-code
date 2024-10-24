# Solution explanation for AoC 2023 Day 20

## Part 1

** To be filled **

## Part 2

* Assumption #1: There is only 1 module pointing to rx
* Assumption #2: The final module before rx is a conjunction
* Assumption #3: The modules on semi_final_layer signal high in regular intervals / cycles

Our result would then be the least common multiple of the periods.

I should note, however, that this is a bit loosey-goosey. Technically, I’m not exactly checking the correct period. The high signals must also line up inside the signal processing loop, i.e. on the correct signal count offset. However, the answer this approach generated was accepted as correct.
