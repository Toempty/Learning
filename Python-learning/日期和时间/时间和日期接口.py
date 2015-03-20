#-------------------------------------------------------------------------------
# Name:        日期和时间接口
# Purpose:
#
# Author:      Administrator
#
# Created:     19/02/2014
# Copyright:   (c) Administrator 2014
# Licence:     <your licence>
#-------------------------------------------------------------------------------


from datetime import date

#系统时间
print("系统时间")
now = date.today()
print(now)
print(now.year)
print(now.month)
print(now.day)

#日期相减
print("\n日期相减")
birthday = date(1989, 9, 5)
age = now - birthday
print(age)
print(age.days)

#日期相加
print("\n日期相加")
tomorrow = now.replace(day = now.day + 1)
print(tomorrow)

#判断输入时间是星期几
#注意weekday() 返回的是0-6是星期一到星期日
print("\n判断输入时间是星期几")
print(now.weekday())
print(tomorrow.weekday())
