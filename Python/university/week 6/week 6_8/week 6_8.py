
animal_id = dict()
with open("input.txt", 'r') as file:
    for line in file:
        line = line.strip().split()
        if line[1] in animal_id:
            animal_id[line[1]].append(line[0])
        else:
            animal_id[line[1]] = [line[0]]

for animal in sorted(animal_id,key=len):
    print(animal,":",sep='',end=' ')
    print(*sorted(animal_id[animal]),sep=', ')