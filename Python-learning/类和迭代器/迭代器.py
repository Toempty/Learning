#-------------------------------------------------------------------------------
# Name:        杩唬鍣?
# Purpose:
#
# Author:      Administrator
#
# Created:     19/02/2014
# Copyright:   (c) Administrator 2014
# Licence:     <your licence>
#-------------------------------------------------------------------------------

for element in [1, 2, 3]:
    print(element)

for element in (1, 2, 3):
    print(element)

for key in {'one':1, 'two':2}:
    print(key)

for char in "123":
    print(char)

for line in open("myfile.txt"):
    print (line)