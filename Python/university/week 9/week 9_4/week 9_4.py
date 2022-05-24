import pandas as pd

data = pd.read_csv("input.txt")
factor = 1.5
plan = data.sum().mean()
data = data.cumsum()



res = {name: [day+1 for day in data.index if data[name][day] > plan] for name in data}
for key,val in res.items():
    if val:
        print(key,val[0])

'''
map_ = dict()
map_ = {name: [index for index in range(5) if index > name] for name in range(3,5)}
print(map_)

for name in data:
      if data[name].sum() > factor*plan:
        for day,number in zip(range(1, data.shape[1]+1),data.cumsum()[name]):
            if number >= plan:
                #print(name, day)
                map_[name] = day
                break
            
sorted_map = dict(sorted(map_.items(), key = lambda s: s[0]))
for key,val in sorted_map.items():
    print(key,val)'''