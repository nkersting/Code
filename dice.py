#!/usr/bin/env python

import random

def AssignSides(sides, N):
    for i in range(N):
        sides.append(random.randint((i)**2 + 1,(i+1)**2))
    return

##########################


N = 6
sides = []
AssignSides(sides, N)
print sides

badsides = [i for i in range(1,N+1)]
badsums = []
for side1 in badsides:
    for side2 in badsides:
        badsums.append(side1 + side2)

print sorted(badsums)

sums = []
for side1 in sides:
    for side2 in sides:
        sums.append(side1 + side2)


print sorted(sums)
