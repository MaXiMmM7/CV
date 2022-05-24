import numpy as np

numbers = np.loadtxt("input.txt")
print("%.2f" % np.median(numbers),"%.2f" % np.mean(numbers),"%.2f" % np.std(numbers))