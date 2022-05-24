numbers=list()
with open("med_research.txt",'r') as read_file:
    for line in read_file:
        numbers.append([float(i) for i in line.split()])
    
res=list()
for i in range(len(numbers[0])):
    res.append([str(j[i]).rstrip("0").rstrip(".") for j in numbers])
    
with open("output.txt",'w') as write_file:
        for line in res:
            write_file.write(" ".join(line)+"\n")
 