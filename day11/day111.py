rack = {}
stack = []
with open("inputfile.txt", "r") as f:
    for line in f:
        part = line.split(":")
        In = part[0]
        out= part[1].strip(" \n").split(" ")
        rack[In]=out

for i in rack['you']:
    stack.append(i)

count=0
while(stack!=[]):
    top= stack[-1]
    stack.pop()
    if rack[top][0]=='out':
        count+=1
        continue
    for i in rack[top]:
        stack.append(i)
print(count)        
