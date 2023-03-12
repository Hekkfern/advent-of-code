


part 2

Myself and 2 other work colleagues collaboratively worked out an extremely efficient solution to Part 2.

Algorithm:

    For each scanner generate 4 coordinates based on the beacon's manhattan distance. For example a scanner at (0, 0) with beacon at (2, 0) the points are (0, 2), (0, -2), (2, 0) and (-2, 0).

    Rotate these points 45 degrees and scale by √2 using the rotation matrix [1, -1] [1, 1] This transforms each scanner into an axis aligned bounding box (AABB). For example the points above become (-2, -2), (2, -2), (-2, 2) and (2, 2).

    For each scanner collect all 4 points and the 2 horizontal and 2 vertical lines making up the box. For example the above scanner has 2 horizontal lines: (-2, -2) -> (2, -2) and (-2, 2) to (2, 2).

    Check every pair of horizontal and vertical lines for intersection. If they intersect then collect this point. For example the line (-2, -2) -> (2, -2) intersects with (0, -4) -> (0, 0) at the point (0, -2). Add these extra points to the points from the 4 corners of every beacon.

    Search the points looking for one that has 3 neighbors exactly 2 away in the x and y axes, for example (0, 0), (0, 2), (2, 0) and (2, 2). This is the rotated location of the distress beacon.

    Transform this beacon back to original coordinates by getting the center of the box, for example (1, 1) in the example above, then multiplying by the inverse rotation matrix (also scaling by √2) [1 1] [-1 1]

    Divide the coordinates by 2 and that is the (x,y) of the distress beacon for the answer.