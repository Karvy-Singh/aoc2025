import numpy as np
from scipy.optimize import Bounds, LinearConstraint, milp

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

total = 0
for idx in range(len(alljoltages)):
    joltage = alljoltages[idx].strip("{}").split(",")
    numjoltage = [int(i) for i in joltage]

    numalloptions = []
    for option in alloptions[idx]:
        numoption = [0] * len(numjoltage)
        option = option.strip("()").split(",")
        for i in option:
            numoption[int(i)] = 1
        numalloptions.append(numoption)

    # https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.milp.html, legit copied shit
    A = np.array(numalloptions).T # transpose for solving, maths like
    b = np.array(numjoltage)
    c = np.ones(len(numalloptions)) #number of button are to be minimised, so c is that 
    integrality = np.ones_like(c)
    constraints = LinearConstraint(A, b, b) #lower bound == upper bound == b means A @ x = b 
    result = milp(
        c=c,
        constraints=constraints,
        integrality=integrality,
    )

    solution_sum = int(round(sum(result.x)))
    total += solution_sum
print(total)
