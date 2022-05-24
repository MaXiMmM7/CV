import numpy as np
import scipy.linalg as s

A = np.array([[4, 2, 2],
             [4, 0, 4],
             [0, 0, 1]])

P,L,U = s.lu(A)
print(np.trace(U))