import math

def prime_factorize(x):
  li = []
  while x >= 2:
    until = int(math.sqrt(x))+1
    for i in xrange(2,until):
      if not x%i:
        li.append(i)
        break
    else:
      li.append(x)
      return li
    x //= i


print prime_factorize(345528117569)
