from metaphone import doublemetaphone
import sys
if len(sys.argv) < 2:
  print "NILL:NILL"
else:
  word = sys.argv[1]
  list_word = doublemetaphone(word)
  one =" "
  if(len(list_word[0]) > 0 ):
   one = list_word[0]
  two = " "
  if(len(list_word[1]) > 0):
   two = list_word[1]
  print one+":"+two 

