import numpy as np

A = np.array([[1,2,3],
              [2,4,6],
              [1,10,1]])
Q,R =np.linalg.qr(A)

print(R,(R[0][0]*R[1][1]*R[2][2]))