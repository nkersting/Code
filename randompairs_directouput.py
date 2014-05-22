#!/usr/bin/env python


#######################################################################
# This code compares random pairs of messages (N words each) to compute
# overlap.
# Output is a list of all matching percentages, which can then be
# historgrammed to find average matching percentage and s.d.
#######################################################################

import csv
import sys
import shlex
import time
import random


#########################################

def uniq(list):
    set = {}
    return [set.setdefault(x,x) for x in list if x not in set]

#########################################


def add_words(word, syns):
    total=[]
    for test in syns:
        if test[0] == word:
            for j in range (1,len(test)):
                total.append(test[j])
    return total

###########################################

def compute_list(userwords, syns):
    

    sumlist = []
    for i in range(0,len(userwords)):        # all possible word pairs considered
        for j in range(i+1, len(userwords)):  
            word1 = userwords[i]
            word2 = userwords[j]
                                  
            uniqtotal1 = uniq(add_words(word1,syns))  # find the set of synsets associated with this word
            uniqtotal2 = uniq(add_words(word2,syns))
           
            for w1 in uniqtotal1:         # take the Cartesian product of the two sets
                for w2 in uniqtotal2:
                    sumlist.append(int(w1)+int(w2)) # this is the heart of the secure algorithm;
                                                # the sum retains information about the individual synsets,
                                                # but is impossible to resolve back into its constituents
            
    return uniq(sumlist)

#########################################
def randomlist(N, syns):

    list = []
    for i in range (0,N):
        theword = syns[random.randint(0, len(syns))][0]
        list.append(theword)

    
    return list
##########################################


def compute_match(list1, list2):

    set1 = set(list1)
    set2 = set(list2)
    minlen = min(len(list1), len(list2))
    overlap = len(set1.intersection(set2))
    return 100*(1.0 * overlap / minlen)
                


###########################################

N = 20             # number of words in each sentence
M = 1000            # number of trials
synfile = "wordsets-full.txt"    # this is a combination of "word-synsets.txt" and "synsets.txt", such that
                            # each word is followed by its primary and secondary synset numbers.

saveplace = "random_matching" + time.strftime("%Y_%m_%d_%H_%M_%S_%P") + ".txt"
outfile = open(saveplace, "w")

synReader = csv.reader(open(synfile,'rb'), delimiter=' ')

syns = []
for synline in synReader:
    syns.append(synline)


for i in range (0,M):


    userwords1 = randomlist(N, syns)
    userwords2 = randomlist(N, syns)


    list1 = compute_list(userwords1, syns)
    list2 = compute_list(userwords2, syns)

    percent = compute_match(list1, list2)

    outfile = open(saveplace, "a")
    outfile.write(str(percent) + '\n')
    outfile.close()

