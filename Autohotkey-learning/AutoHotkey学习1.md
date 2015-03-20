
### AutoHotkey 学习

#### 使用方法
> 1. 新建文本文档
> 2. 写入AutoHotkey命令
> 3. 保存，后缀名为ahk

对于常用命令可以直接保存在“C:\Users\Administrator\Documents”目录下的AutoHotkey.ahk文件内。
#### 一.run命令
1. 打开网页 
> run, http://www.baidu.com

2. 打开记事本
> run, notepad

3. 打开QQ
> run, D:\QQ 2013\Bin\QQ.exe

4. 打开Everything
> run, D:\EveryThing_X64\Everything.exe

5. 打开文件夹
> run, explore D:\


#### 二.常见的修饰键符号来定义的热键
符号      描述

\#     表示键盘上的Windows键

!      Alt

^      Control

\+     Shift

~     当激发热键时，按键的原来的功能不会被屏蔽(被操作系统隐藏)。

::    意味着每次按下此热键时，随后的命令将会被执行

******
> 例子
******
> 用alt+q快捷键快速打开qq程序

> !q::run,c:\QQ\QQ2011\Bin\QQ.exe 
******
> 用alt+2快捷键快速打开文件夹

> ~!2::Run,explore D:\
******