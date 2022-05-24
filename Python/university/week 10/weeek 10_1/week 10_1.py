import pandas as pd

data = pd.read_csv("input.txt", delimiter = ',')
data.dropna(axis = 0,how = "any",subset = ["name"], inplace = True)
data.fillna({"score": data["score"].mean()},axis = 0, inplace = True)
data.to_csv("output.txt", index = True)