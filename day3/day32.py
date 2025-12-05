import textwrap

with open("inputfile.txt","r") as f:
    total=0
    for battery in f:
        eachbat=textwrap.wrap(battery,1)
        intbat=[int(i) for i in eachbat]
        stack=[]
        for i in intbat[:-12]:
            if stack==[]:
                stack.append(i)
            elif stack[-1]<i:
                while(stack and stack[-1]<i):
                    stack.pop()
                stack.append(i)
            else:
                stack.append(i)
        left=intbat[-12::]
        #print(stack)
        #print(left)
        for i in range(0,12):
            #print(i)
            #allowed=len(left[i::])
            if stack[-1]<left[i]:
                while(stack and stack[-1]<left[i] and len(stack)+len(left[i::])>12):
                    #print(stack)
                    #print(left[i::])
                    #allowed-=12

                    stack.pop()
                stack.append(left[i])
                #print(stack)
                #print(left[i::])
            elif len(stack)!=12:
                stack.append(left[i])
                #print(stack)
        print(stack[0:12])
        num=0
        for i in stack[0:12]:
            num=num*10+i
        total+=num
    print(total)





    
    #     total=0
    #     for battery in f:
    #         eachbat=textwrap.wrap(battery,1)
    #         intbat=[int(i) for i in eachbat]
    #         maxb=max(intbat)
    #         indexes=[]
    #         maxbb=0
    #         maxbat=0
    #         maxbatf=0
    #         numbers=[9,8,7,6,5,4,3,2,1]
    #         for i in numbers:
    #             maxbat=i
    #             indexes= [j for j, x in enumerate(intbat) if x == i]
    #             choices=[]
    #             if len(indexes)==0:
    #                 continue
    #             if len(intbat[indexes[0]::])<11:
    #                 continue
    #             for index in indexes:
    #                 if len(intbat[index+1::])>=11:
    #                     choices= list(enumerate(intbat[index+1::]))
    #                     choices=sorted(choices,key=lambda item: item[1], reverse=True)
    #                     choices=choices[:11]
    #                     choices=sorted(choices,key=lambda item: item[0], reverse=True)
    #                 else: 
    #                     continue
    #                 for i in choices:
    #                     maxbat=maxbat*10+i[1]
    #                 if maxbat>maxbatf:
    #                     maxbatf=maxbat 
    #             if maxbatf!=0:
    #                 break
    #             #print(maxbat)
    #         total+=maxbatf
    #     print(total)

    
