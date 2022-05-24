import numpy as np

with open("input.txt",'r') as file_in:
    first_income,last_income,days = file_in.read().strip().split()

plan = np.linspace(int(first_income),int(last_income),int(days))
plan[::7]=plan[::7]/3
plan[4::7]=plan[4::7]*2

with open("output.txt",'w') as file_out:
    for number in plan:
        file_out.write("%.2f \n" % number)