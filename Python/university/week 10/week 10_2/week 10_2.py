import pandas as pd

def t_f(t_c):
    return round(((9/5)*t_c+32))

data = pd.read_csv("input.txt")
data["temperature_f"] = data["temperature_c"].apply(t_f)
data.to_csv("output.txt")