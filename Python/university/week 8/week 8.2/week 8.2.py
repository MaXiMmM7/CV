import numpy as np

with open("input.txt", 'r') as file:
    ar = np.loadtxt(file,delimiter = ',',dtype = int)
    f = np.sum(ar[::,0:1])
    s = np.sum(ar[::,1:2])
    t = np.sum(ar[::,2:3])    
    if f > s:
        max = 1
        h = f
    else:
        max = 2
        h = s
    if h < t:
        max = 3
    print(max)