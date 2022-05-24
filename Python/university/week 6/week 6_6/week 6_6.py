
male = set()
female = set()
with open("input.txt",'r') as file:
    for line in file:
        line = line.strip().split()
        name,gender = line[1],line[2]
        if gender == "male":
            male.add(name)
        else:
            female.add(name)



sorted_animals = sorted((male & female),key=len)        
if sorted_animals:    
    for i in sorted_animals:
        print(i)
else:
    print(0)