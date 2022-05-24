import numpy as np

with open("input.txt", 'r') as file:
    data = np.loadtxt(file, delimiter = ',',dtype = float)
    data[1::2,0::2]=data[1::2,0::2]/2
    data[0::2,1::2]=data[0::2,1::2]/2
    np.savetxt("output.txt", data, fmt = '%g', delimiter = ',')
    
