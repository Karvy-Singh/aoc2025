rack = {}
with open("inputfile.txt", "r") as f:
    for line in f:
        part = line.split(":")
        In = part[0]
        out = part[1].strip(" \n").split(" ")
        rack[In] = out

from functools import lru_cache


@lru_cache(None)
def dfs(node, seen_fft, seen_dac) -> int:
    if node == 'fft':
        seen_fft = True
    if node == 'dac':
        seen_dac = True
    if node == "out":
        if seen_fft and seen_dac:
            return 1
        else:
            return 0
    total = 0
    for nxt in rack[node]:
        total += dfs(nxt, seen_fft, seen_dac)
    return total
print(dfs('svr',False,False))

