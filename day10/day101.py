alllights = []
alloptions = []
alljoltages = []

with open("./inputfile.txt", "r") as f:
    for line in f:
        parts = line.strip("\n").split(" ")
        light = parts[0]
        joltage = parts[-1]
        parts.pop()
        options = parts[1:]
        alllights.append(light)
        alloptions.append(options)
        alljoltages.append(joltage)


def change(arr1, arr2):
    ans = []
    for i in range(len(arr1)):
        ans.append(arr1[i] ^ arr2[i])
    # print(arr1)
    return ans


idx = -1
total = 0
for light in alllights:
    idx += 1
    light = light.strip("[]")
    numlight = []
    for i in light:
        if i == ".":
            numlight.append(0)
        if i == "#":
            numlight.append(1)
    # print(numlight)

    numalloptions = []

    for option in alloptions[idx]:
        numoption = [0 for i in range(len(numlight))]
        option = list(option.strip("()").split(","))
        for i in option:
            numoption[int(i)] = 1
        numalloptions.append(numoption)

    save = []

    def dfs(arr, n, idx, given, target, chosen):
        if given == target:
            save.append(chosen)
            return
        if idx == n:
            return

        dfs(arr, n, idx + 1, change(given, arr[idx]), target, chosen + 1)
        dfs(arr, n, idx + 1, given, target, chosen)

    dfs(
        numalloptions,
        len(numalloptions),
        0,
        [0 for i in range(len(numlight))],
        numlight,
        0,
    )
    mini = 100
    for i in save:
        if i < mini:
            mini = i
    total += mini
print(total)
