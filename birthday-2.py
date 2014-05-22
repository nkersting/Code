#!/usr/bin/env python


"""
This code generalizes the birthday problem:  how many users are needed to get a 50% chance of at least two identical words in a n-word submission
"""


nUsers = 53      
nWords = 2000  # typical office vocabulary
nSubmit = 10 # number of words in the submission


prob = 1.0
for i in range (1,nUsers):
    prob = 1.0*prob*(nWords-1.0*i)/nWords

print 1.0 - 1.0*prob
