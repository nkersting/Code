#!/usr/bin/env python

import csv

Reader = csv.reader(open('key-word-freq-sorted3.txt','rb'), delimiter=' ')

count = 0
total = 0

for line in Reader:
    count += 1
    total += int(line[2])


print "%s lines totalling %s "  % (count, total)
