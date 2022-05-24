map_=dict()
weights=list()
with open("weights.txt",'r') as read_file:
    for line in read_file:
        name,weight = line.split()
        map_[float(weight)]=name
        weights.append(float(weight))

weights.sort(reverse=True)
team_1=weights[::2]
team_2=weights[1::2]
with open("team.txt",'w') as write_file:
    for w in team_1:
        write_file.write(""+map_[w]+" "+str(w)+"\n")
    for w in team_2:
        write_file.write(""+map_[w]+" "+str(w)+"\n")