
from metaphone import doublemetaphone
filename = 'dict.txt'
file_content = open(filename,'r').read().split()
#print file_content

file_out = "dict1"
file_output = open(file_out,'w')

for word in file_content:
	word_list = doublemetaphone(word)
	output = str(word_list[0]+"\n"+word_list[1]+"\n")
	file_output.write(output)
	
