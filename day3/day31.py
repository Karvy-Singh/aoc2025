import textwrap
with open("inputfile.txt","r") as f:
    total=0
    for battery in f:
        eachbat=textwrap.wrap(battery,1)
        intbat=[int(i) for i in eachbat]
        maxb=max(intbat)
        indexes=[]
        maxbb=0
        maxbat=0
        maxbatf=0
        for i in range(0,len(intbat)):
            if intbat[i]==maxb:
                indexes.append(i)
        #print(index)
        #print(len(eachbat)-1)
        for index in indexes:
            if index==(len(eachbat)-1):
                #print(intbat[0:index])
                maxbb= max(intbat[0:index])
                maxbat=maxbb*10+maxb
            elif index==0:
                maxbb= max(intbat[1::])
                maxbat=maxb*10+maxbb
            else:
                #print(intbat[(index+1)::])
                maxbb= max(intbat[(index+1)::])
                maxbat= maxb*10+maxbb
            if maxbat>maxbatf:
                maxbatf=maxbat
        #print(maxbat)
        total+=maxbatf
    print(total)

        
