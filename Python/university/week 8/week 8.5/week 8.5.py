import numpy as np

with open("input.txt", 'r') as file:
    data = np.loadtxt(file, delimiter = ',', dtype = int)
    for i in range(len(data[0])):
        data[0,i]=int(1.5*np.mean(data[:,i]))
    np.savetxt("output.txt", data, delimiter = ',', fmt = '%d')
    