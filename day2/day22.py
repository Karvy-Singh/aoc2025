import textwrap

input=""
# ranges= input.split(",")
# total=0;
# for i in ranges:
#     start= i.split("-")[0]
#     stop= i.split("-")[1] 
#     for j in range(int(start),int(stop)+1):
#         freq={}
#         j=str(j)
#         for l in j:
#             if l in freq:
#                 freq[l]+=1 
#             else:
#                 freq[l]=1
#         #print(freq)
#         flag=1 
#         eachcount=freq[j[0]]
#         for m in freq:
#             if freq[m]!=eachcount:
#                 flag=0
#                 break
#         if(flag==1):
#             #print(freq)
#             parts=textwrap.wrap(j,eachcount)
#             #print(parts)
#             duplicates={}
#             for part in parts:
#                 if part in duplicates:
#                     duplicates[part]+=1 
#                 else:
#                     duplicates[part]=1
#             if(len(duplicates)==1):
#                 total+=int(j)
# print(total)

ranges= input.split(",")
total=0;
for i in ranges:
    start= i.split("-")[0]
    stop= i.split("-")[1] 
    for j in range(int(start),int(stop)+1):
        j=str(j)
        rep=""
        for l in j:
            if rep=="":
                rep+=l
            elif not(l==rep[0] and rep==j[-(len(rep)):]):
                rep+=l
            else: 
                break
        #print(rep)
        parts=textwrap.wrap(j,len(rep))
        #print(parts)
        if len(parts)!=1:
            duplicates={}
            for part in parts:
                if part in duplicates:
                    duplicates[part]+=1 
                else:
                    duplicates[part]=1
            if(len(duplicates)==1):
                print(parts)
                total+=int(j)

print(total)
