#-------------------------------------------------------------------------------
# Name:        test
# Purpose:
#
# Author:      Administrator
#
# Created:     18/02/2014
# Copyright:   (c) Administrator 2014
# Licence:     <your licence>
#-------------------------------------------------------------------------------

#单行注释

num_int = 1
num_float = 1.1


print (num_int)
print (num_float)

'''
多行注释
还是注释
单引号，双引号，三双引号
'''
string = 'a'
string_1 = "a"
strings = 'It\'s "a" string!'
strings_1 = "1:It\'s 'a' string!"
strings_2 = "2:It\'s a string! \
2:It\'s a string!"
strings_3 = '3:It\'s a string! \
3:It\'s a string!'
strings_4 = """4:It\'s a string! \
4:It\'s a string!
4:It\'s a string!"""
strings_5 = strings_1 + ' ' + strings_2

print (string)
print (string_1)
print (strings)
print (strings_1)
print (strings_2)
print (strings_3)
print (strings_4)
print (strings_5)