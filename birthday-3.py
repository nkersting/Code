#!/usr/bin/env python


"""
This code generalizes the birthday problem: what is the probability that at least 3 have the same birthday?
"""

nUsers = 44  # number of US presidents
nWords = 365




probNoneSame = 1.0
for i in range (1,nUsers):
    probNoneSame = 1.0*probNoneSame*(nWords-1.0*i)/nWords

probTwoSame = (nUsers)*(nUsers - 1)/2.0/nWords
for i in range (1,nUsers-1):
    probTwoSame = 1.0*probTwoSame*(nWords-1.0*i)/nWords





print 1.0 - 1.0*probNoneSame - 1.0*probTwoSame

