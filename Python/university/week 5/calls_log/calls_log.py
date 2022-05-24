with open("the_calls.txt","r") as file_read,open("calls.txt","w") as file_write:
    calls =[line.split("\t") for line in file_read.read().split("\n")]
    calls.sort(key=lambda x: int(x[1]),reverse=True)
    for line in list(filter(lambda x: x[2]=="A",calls)):
        file_write.write("\t".join(line)+"\n")
    for line in list(filter(lambda x: x[2]=="B",calls)):
        file_write.write("\t".join(line)+"\n")        