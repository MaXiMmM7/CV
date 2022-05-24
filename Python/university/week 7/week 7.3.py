
with open("input.txt",'r') as file:
    lst = [int(date) for date in file.read().strip().split()]
left = 0
right = len(lst)-1
while (right - left) > 1:
    middle = (right + left) // 2
    if lst[middle] < 1415:
        left = middle
    else:
        right = middle
        
print(right)        
    
