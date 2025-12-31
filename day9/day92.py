from bisect import bisect_right

allnums = []
with open("./inputfile.txt", "r") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        x, y = line.split(",")
        allnums.append([int(x), int(y)])

points = list(map(tuple, allnums))

out = []
for (x1, y1), (x2, y2) in zip(allnums, allnums[1:] + allnums[:1]):
    out.append([x1, y1])
    if x1 == x2:
        out += [[x1, y] for y in range(min(y1, y2) + 1, max(y1, y2))]
    elif y1 == y2:
        out += [[x, y1] for x in range(min(x1, x2) + 1, max(x1, x2))]
boundary = set(map(tuple, out))

# for every crude minded ppl out there, segs means segment
vsegs = []  
hsegs = []  
for (x1, y1), (x2, y2) in zip(points, points[1:] + points[:1]):
    if x1 == x2:
        a, b = (y1, y2) if y1 < y2 else (y2, y1)
        vsegs.append((x1, a, b))
    elif y1 == y2:
        a, b = (x1, x2) if x1 < x2 else (x2, x1)
        hsegs.append((y1, a, b))

Yvals = sorted(set(y for _, y in points))
cross = {}  

for y in Yvals:
    xs = []
    for x, a, b in vsegs:
        if a <= y < b:   
            xs.append(x)
    xs.sort()
    cross[y] = xs

def inside(px, py):
    if (px, py) in boundary:
        return True
    xs = cross.get(py, [])
    k = bisect_right(xs, px)      
    return ((len(xs) - k) % 2) == 1

def overlap(a, b, lo, hi):
    return max(a, lo) < min(b, hi)

def boundary_cuts_rect(xmin, xmax, ymin, ymax):
    # any boundary segment intersects the open interior? then rectangle not fully inside
    for x, a, b in vsegs:
        if xmin < x < xmax and overlap(a, b, ymin, ymax):
            return True
    for y, a, b in hsegs:
        if ymin < y < ymax and overlap(a, b, xmin, xmax):
            return True
    return False

maxarea = 0
for i in points:
    for j in points:
        x1, y1 = i
        x2, y2 = j
        xmin, xmax = (x1, x2) if x1 < x2 else (x2, x1)
        ymin, ymax = (y1, y2) if y1 < y2 else (y2, y1)
        area = (xmax - xmin + 1) * (ymax - ymin + 1)
        if area <= maxarea:
            continue
        # all four corners must be inside/on boundary
        if not (inside(xmin, ymin) and inside(xmin, ymax) and inside(xmax, ymin) and inside(xmax, ymax)):
            continue
        # boundary must not cut through rectangle interior (concavity trap fix)
        if boundary_cuts_rect(xmin, xmax, ymin, ymax):
            continue
        maxarea = area
        chosen1 = i
        chosen2 = j
print(maxarea)

