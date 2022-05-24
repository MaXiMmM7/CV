from collections import Counter

with open("input.txt",'r') as file:
    animals_count = Counter(line.strip().split()[1] for line in file)

sorted_animals = animals_count.most_common();

for animal,count in sorted_animals:
    print(animal,count,sep=" - ")