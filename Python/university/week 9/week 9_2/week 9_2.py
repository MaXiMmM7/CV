import pandas as pd

data = pd.read_csv("input.txt")
max_ = data.min().min()
for i in data.columns:
    mean_ = data[i].mean()
    if max_ < mean_:
        max_ = mean_
        name = i
print(name)