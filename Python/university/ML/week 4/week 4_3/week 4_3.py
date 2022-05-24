import numpy as np
import scipy

A = np.array([[10,0,0],
              [0,-2,0],
              [0,0,0]])
A_ = scipy.linalg.pinv(A)
print(A_,np.trace(A_))
'''import numpy as np
import scipy.linalg as sl

A = np.array([[10,0,0],
              [0,-2,0],
              [0,0,0]])
A_ = sl.pinv(A)
print(A_,np.trace(A_))'''