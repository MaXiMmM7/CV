import pandas as pd
import numpy as np

data = pd.read_csv("input.txt", delimiter = ',',header = None)
A = np.array([data[j].mean() for j in data])
print(np.where(A == A.min())[0][0]+1)