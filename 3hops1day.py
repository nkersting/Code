#!/usr/bin/env python

import csv



Jan9_1_file = 'Jan9-1loads.txt'  # each of these files is space-delimited, of form "OSSN1 OSSN2" on each line
Jan9_0_file = 'Jan9-0loads.txt'
Jan10_0_file = 'Jan10-0loads.txt'

Jan9_1_LoadReader = csv.reader(open(Jan9_1_file,'rb'), delimiter=' ')
Jan9_0_LoadReader = csv.reader(open(Jan9_0_file,'rb'), delimiter=' ')
Jan10_0_LoadReader = csv.reader(open(Jan10_0_file,'rb'), delimiter=' ')

def uniq(list):
    set = {}
    return [set.setdefault(x,x) for x in list if x not in set]

# --- uniq ----


Jan9_1_Hops = []
Jan9_0_Hops = []
Jan10_0_Hops = []


loads1 = []
for firstload in Jan9_1_LoadReader:
    loads1.append(firstload[0])
    Jan9_1_Hops.append(firstload)

loads2 = []
for secondload in Jan9_0_LoadReader:
    loads2.append(secondload[0])
    Jan9_0_Hops.append(secondload)

loads3 = []
for load in Jan10_0_LoadReader:
    Jan10_0_Hops.append(load)





originloads = []                   # compile list of all origins
for load in loads1:
    originloads.append(load)

for load in loads2:
    originloads.append(load)


originloads = uniq(originloads)    # compile list of unique origins



sum = 0
count = 0
print "Total of %s unique origins" % (len(originloads))
for originload in originloads:
    count += 1
    destlist = []    



    
    for firstload in Jan9_0_Hops:          # 0^n, n=1
        if originload == firstload[0]:
            destlist.append(firstload[1])


    
    for firstload in Jan9_0_Hops:          # 0^n, n=2
        if originload == firstload[0]:
            for secondload in Jan9_0_Hops:
                if secondload[0] == firstload[1]:
                    destlist.append(secondload[1])



    
    for firstload in Jan9_0_Hops:          # 0^n, n=3
        if originload == firstload[0]:
            for secondload in Jan9_0_Hops:
                if secondload[0] == firstload[1]:
                    for thirdload in Jan9_0_Hops:
                        if thirdload[0] == secondload[1]:
                            destlist.append(thirdload[1])




    
    for firstload in Jan9_1_Hops:          # 0^m 1 0^n, (m,n) = (0,0)
        if originload == firstload[0]:
            destlist.append(firstload[1])


    
    for firstload in Jan9_0_Hops:          # 0^m 1 0^n, (m,n) = (1,0)
        if originload == firstload[0]:
            for secondload in Jan9_1_Hops:
                if secondload[0] == firstload[1]:
                    destlist.append(secondload[1])

    
    for firstload in Jan9_1_Hops:          # 0^m 1 0^n, (m,n) = (0,1)
        if originload == firstload[0]:
            for secondload in Jan10_0_Hops:
                if secondload[0] == firstload[1]:
                    destlist.append(secondload[1])




    for firstload in Jan9_0_Hops:          # 0^m 1 0^n, (m,n) = (1,1)
        if originload == firstload[0]:
            for secondload in Jan9_1_Hops:
                if secondload[0] == firstload[1]:
                    for thirdload in Jan10_0_Hops:
                        if thirdload[0] == secondload[1]:
                            destlist.append(thirdload[1])


    for firstload in Jan9_0_Hops:          # 0^m 1 0^n, (m,n) = (2,0)
        if originload == firstload[0]:
            for secondload in Jan9_0_Hops:
                if secondload[0] == firstload[1]:
                    for thirdload in Jan9_1_Hops:
                        if thirdload[0] == secondload[1]:
                            destlist.append(thirdload[1])



    for firstload in Jan9_1_Hops:          # 0^m 1 0^n, (m,n) = (0,2)
        if originload == firstload[0]:
            for secondload in Jan10_0_Hops:
                if secondload[0] == firstload[1]:
                    for thirdload in Jan10_0_Hops:
                        if thirdload[0] == secondload[1]:
                            destlist.append(thirdload[1])





    if len(destlist) != 0:
        print count, len(destlist),len(uniq(destlist)), 1.0*len(destlist)/len(uniq(destlist))
        sum = sum + 1.0*len(destlist)/len(uniq(destlist))

# below the average number of paths is printed
print sum/len(originloads)
