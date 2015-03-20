#-------------------------------------------------------------------------------
# Name:        生成器
# Purpose:
#
# Author:      Administrator
#
# Created:     19/02/2014
# Copyright:   (c) Administrator 2014
# Licence:     <your licence>
#-------------------------------------------------------------------------------

def reverse(data):
    for index in range(len(data)-1, -1, -1):
        yield data[index]

for char in reverse("your"):
    print(char)


#just for test
def reverse(data):
    for index in range(0, len(data), 1):
        yield data[index]

for char in reverse("your"):
    print(char)


# just some examples
sum10 = sum(i*i for i in range(10))                 # sum of squares
print(sum10)

xvec = [10, 20, 30]
yvec = [7, 5, 3]
sumxy = sum(x*y for x,y in zip(xvec, yvec))         # dot product
print(sumxy)

from math import pi, sin
sine_table = {x: sin(x*pi/180) for x in range(0, 91)}
print(sine_table)

#unique_words = set(word  for line in page  for word in line.split())


#valedictorian = max((student.gpa, student.name) for student in graduates)


data = 'golf'
data_list = list(data[i] for i in range(len(data)-1, -1, -1))
print(data_list)