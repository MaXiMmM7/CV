import itertools as it

x = (True,False)

lst = list()
for x1,x2,x3 in it.product(x,x,x):
    if (((not x1 and x2 and not x3)or(not x1 and x2 and x3) 
         or (x1 and not x2 and not x3))== True):
       lst.append(str(x1)+" "+ str(x2)+" "+str(x3))
      

for i in sorted(lst):
    print(i)
    