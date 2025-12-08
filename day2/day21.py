input=""
ranges= input.split(",")
total=0;
for i in ranges:
    start= i.split("-")[0]
    stop= i.split("-")[1] 
    for j in range(int(start),int(stop)+1):
        j=str(j)
        if(len(j)%2==0):
            part1=j[0:int(len(j)/2)]
            part2=j[int(len(j)/2):]
            #print(part1, part2)
            if(part1==part2):
                total+=int(j)
print(total)

