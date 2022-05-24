
animals = set()
with open("input.txt",'r') as file:
    for line in file:
        animals.add(line.strip().split()[1])
        
sorted_by_len_animals = sorted(animals,key=len)
for i in sorted_by_len_animals:
    print(i)