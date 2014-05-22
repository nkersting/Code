

sent = ['Take', 'care', 'of', 'the', 'sense', ',', 'and', 'the', 'sounds', 'will', 'take', 'care', 'of', 'themselves', '.']

print sorted(sent, lambda x,y: cmp(len(x),len(y)))

print sorted(sent, lambda x,y: cmp(len(x)*len(y), len(x)+ 3*len(y)))
