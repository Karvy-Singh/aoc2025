allnums = []
with open("./inputfile.txt", "r") as f:
    for line in f:
        nums = line.split(",")
        nums = [int(i) for i in nums]
        allnums.append(nums)
# print(allnums)

maxarea = 0
for i in allnums:
    for j in allnums:
        area = (abs(i[0] - j[0]) + 1) * (abs(i[1] - j[1]) + 1)
        # print(area)
        if area > maxarea:
            maxarea = area
print(maxarea)
