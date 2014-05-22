#!/usr/bin/env python


"""
You are playing Russian Roulette with a friend and
a N chamber gun with n bullets in it. Your friend fires and 'click' it's an empty chamber. If you now fire, what is your chance of getting another empty chamber?
"""

import random
import math

class Gun:
    def __init__(self, chambers = 6, bullets = 2):
        self.chambers = chambers
        self.bullets = bullets


        # load the gun
        self.loaded_chambers = set()
        while (bullets > 0):
            c = random.randint(1,self.chambers)
            if c not in self.loaded_chambers:
                self.loaded_chambers.add(c)
                bullets -= 1

    def PullTrigger(self):   # returns 1 if no bullet in chamber after friend's
#        print '\n'
#        print self.loaded_chambers
        while (1):
            friendChamber = random.randint(1, self.chambers)
            if friendChamber not in self.loaded_chambers:  # constraint: friend lives
                if (friendChamber % self.chambers + 1) not in self.loaded_chambers:
 #                   print "alive " + str(friendChamber)
                    return 1
                else:
 #                   print "dead " + str(friendChamber)
                    return 0


def main():
    nChambers = 6
    nBullets = 2
    nTrials = 1000

    means = []
    for i in range(nTrials):
        thisGun = Gun(nChambers, nBullets)
        results = []
        for j in range(nTrials):
            results.append(thisGun.PullTrigger())
        means.append(1.0 * sum(results) / len(results))

    avgmean = 1.0 * sum(means) / len(means)
    std = 0
    for m in means:
        std += (m - avgmean)*(m - avgmean)
    std = math.sqrt(std / len(means))

    print 'Probability of living is %f +/- %f' % (avgmean, std)



if __name__ == '__main__':
    main()
