#!/usr/bin/env python


"""
This code generalizes the birthday problem:  how many users are needed to get a 50% chance of at least two identical 1-word submissions
"""

nUsers = 23  # birthday problem 50%
# nUsers = 44  # number of US presidents
nWords = 365



#nUsers = 119      
#nWords = 10000  # typical day-to-day vocabulary


#nUsers = 53      
#nWords = 2000  # typical office vocabulary



prob = 1.0
for i in range (1,nUsers):
    prob = 1.0*prob*(nWords-1.0*i)/nWords

print 1.0 - 1.0*prob
