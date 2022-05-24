text=list()
with open("poe_unpublished.txt",'r') as read_file:
    for line in read_file:
        text.append(line.split())
#print(text)
text=[sorted(line,key=len) for line in sorted(text,key=len)]

with open("poe_decode_attempt.txt",'w') as write_file:
    for line in text:
        write_file.write(" ".join(line)+"\n")