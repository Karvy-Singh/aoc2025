import textwrap

input="655-1102,2949-4331,885300-1098691,1867-2844,20-43,4382100-4484893,781681037-781860439,647601-734894,2-16,180-238,195135887-195258082,47-64,4392-6414,6470-10044,345-600,5353503564-5353567532,124142-198665,1151882036-1151931750,6666551471-6666743820,207368-302426,5457772-5654349,72969293-73018196,71-109,46428150-46507525,15955-26536,65620-107801,1255-1813,427058-455196,333968-391876,482446-514820,45504-61820,36235767-36468253,23249929-23312800,5210718-5346163,648632326-648673051,116-173,752508-837824"

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
