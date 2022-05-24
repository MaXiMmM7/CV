import pandas as pd

mersedes = 8000000
total_sum = 0

data = pd.read_csv("input.txt")
max_ = data.min().min()

for i in data.columns:
    sum_ = data[i].sum()
    total_sum += sum_
    if(sum_ > max_):
        max_ = sum_
        name = i

if total_sum < mersedes:
    print(0)
else:
    print(1,name)
    
