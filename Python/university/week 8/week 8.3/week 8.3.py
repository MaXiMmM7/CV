import numpy as np

first,second = 0,0

with open("input.txt",'r') as file:
    ar = np.loadtxt(file, delimiter = ',', dtype = int)
    for line in ar:
        if abs(np.std(line)) <= 4:
            first+=1
        else:
            second+=1
    print(1 if first >= second else 2)