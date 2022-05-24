from collections import Counter

with open("input.txt",'r') as file:
    numbers_counts = Counter(char for char in file.read().strip())

res = numbers_counts.most_common()
print(res[0][0])    