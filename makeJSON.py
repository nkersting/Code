#!/usr/bin/env python

import csv
import random
import math

BuildingsFile = 'buildings.csv'

BuildingsReader = csv.reader(open(BuildingsFile,'rb'), delimiter=',')


print "var voldata = ["

for building in BuildingsReader:
    building_id = building[0]
    building_lat = building[3]
    building_long = building[4]
    building_name = building[5]
#    building_vol = ord(building_name[0])    # item count is determined by first letter of name, ha!
    building_vol = random.randrange(0,2000) 
#    building_errors = random.randrange(0,1+math.floor(abs(float(building_lat))))
    building_errors = random.randrange(0, 1 + math.floor(building_vol*0.1))
    building_name = building_name.replace('\'','')
    print "{ \"building_id\": %s, \"building_lat\": %s, \"building_long\": %s, \"building_name\": '%s', \"building_vol\": %s , \"building_err\": %s }," % (building_id, building_lat, building_long, building_name, building_vol, building_errors)


print "{ \"building_id\": 1, \"building_lat\": 90, \"building_long\": 0, \"building_name\": 'SANTAS WORKSHOP', \"building_vol\": 1  } ]"

