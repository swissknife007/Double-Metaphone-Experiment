filec = open("dict2.txt","r").read().split()
file2 = open("dict3.txt","w")
c = 0
for word in filec:
 if(c==1):
  file2.write(word+"\n")
 c = (c + 1)%4
