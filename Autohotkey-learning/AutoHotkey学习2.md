@(AutoHotkey)[AutoHotkey]
### 快捷键实现

这个部分介绍了如何使用AutoHotkey，用快捷键来实现程序的快速启动以及其他操作。

为了方便，启动AutoHotkey也需要设置快捷键，我设置的是`Ctrl + Alt + ~`

#### 一.AutoHotkey开机启动
1. 创建`AutoHotkey.exe`的快捷方式
2. 将`AutoHotkey.exe`的快捷方式移动到`开机启动`文件夹下，我的是`C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup`
3. 重新启动电脑，`AutoHotkey.exe`将开机启动

#### 二.流程
> 1.打开脚本文件
    
    一般在管理员默认文档目录下，如`C:\Users\Administrator\Documents\AutoHotkey.ahk`
    
> 2.修改脚本
    
    如下图所示：
    
![Alt text](data:image,local://捕获.PNG)

> 3.保存

> 4.重新启动AutoHotkey

> 5.现在就可以使用快捷键启动程序了

#### 三.设置热字符串
在大多数程序的窗口，只有输入设置的热字符串，不管有无文本输入框，都将执行相应的操作

例如：

![Alt text](data:image,local://捕获1.PNG)

如图所示：

> 在任何窗口输入`//b`，然后按回车或空格将在默认浏览器中打开百度

> 在任何窗口输入`//g`，然后按回车或空格将在默认浏览器中打开谷歌