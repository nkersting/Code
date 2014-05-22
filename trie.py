

def insert(trie, key, value):
    if key:
        first, rest = key[0], key[1:]
        if first not in trie:
            trie[first] = {}
        insert(trie[first], rest, value)
    else:
        trie['value'] = value
    return


trie  ={}
insert(trie, 'doggy', 1)
insert(trie, 'doggeral', 1)
insert(trie, 'doggone', 1)

print(trie)



