
# two cases: non-wrapping or wrapping
# For former, use Kadane
# For latter, use Kadane on (-1)*array to find non-contributing segment, and subtract from total sum


def Kadane(vals):
    start = 0
    end = 0
    residual = 0
    sumd = 0
    for i in range(len(vals)):
        # give up
        if (vals[i] > sumd + residual + vals[i]):
            start = i
            end = i
            sumd = vals[i]
            residual = 0
        elif (vals[i] + residual >= 0): # increment
            end = i
            sumd += vals[i] + residual
            residual = 0
        else:  # wait and see
            residual += vals[i]

    return start, end, sumd

vals = [83,-4,0,-1,8,6,-20, 60]
print vals

results1 = Kadane(vals)
results2 = Kadane([-1*x for x in vals]) 

print results1, results2
results = []
if (results1[2] > sum(vals) + results2[2]):
    results = results1
else:
    results = results2[1]+ 1, results2[0] - 1, sum(vals) + results2[2]

print "%d %d, sum = %d" % results


