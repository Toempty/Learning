; IMPORTANT INFO ABOUT GETTING STARTED: Lines that start with a
; semicolon, such as this one, are comments.  They are not executed.

; This script has a special filename and path because it is automatically
; launched when you run the program directly.  Also, any text file whose
; name ends in .ahk is associated with the program, which means that it
; can be launched simply by double-clicking it.  You can have as many .ahk
; files as you want, located in any folder.  You can also run more than
; one .ahk file simultaneously and each will get its own tray icon.

; SAMPLE HOTKEYS: Below are two sample hotkeys.  The first is Win+Z and it
; launches a web site in the default browser.  The second is Control+Alt+N
; and it launches a new Notepad window (or activates an existing one).  To
; try out these hotkeys, run AutoHotkey again, which will load this file.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;url编码解码
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
uriEncode(str)
{
f = %A_FormatInteger%
SetFormat, Integer, Hex

If RegExMatch(str, "^\w+:/{0,2}", pr)
StringTrimLeft, str, str, StrLen(pr)
StringReplace, str, str, `%, `%25, All
Loop

If RegExMatch(str, "i)[^\w\.~%]", char)
StringReplace, str, str, %char%, % "%" . Asc(char), All
Else Break
SetFormat, Integer, %f%
Return, pr . str
}
uriDecode(str)
{
Loop
If RegExMatch(str, "i)(?<=%)[\da-f]{1,2}", hex)
StringReplace, str, str, `%%hex%, % Chr("0x" . hex), All
Else Break
Return, str
}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;url编码解码
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;运行程序
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;win + q ：打开 QQ
#q::Run, D:\QQ\Bin\QQ.exe

;win + s ：打开 sublime text 3
#s::Run, D:\Sublime Text 3\sublime_text.exe

;win + c ：打开 Chrome
;#c::Run, C:\Users\lch\AppData\Local\Google\Chrome\Application\chrome.exe --enable-benchmarking

;win + f ：打开 Everything
#f::Run, D:\Everything64\Everything.exe

;win + g ：打开 飞鸽传书
#g::Run, D:\fei ge chuan shu\IPMSG.exe

;win + k ：打开 金山词霸
#k::Run, D:\PowerWordDict\XDict.exe

;win + n ：打开 evernote
#n::Run, D:\Evernote\Evernote.exe

;win + c : 打开ccleaner清理垃圾
#c::Run, D:\CCleaner\CCleaner64.exe

;win + u : 打开UninstallTool卸载工具
#u::Run, D:\Uninstall Tool\UninstallTool.exe

;win + x : 打开思维导图XMind
#x::Run, D:\XMind\XMind.exe

;win + h : 清理回收站
#h::FileRecycleEmpty

;win + t: 打开ftp
#t::Run, D:\FlashFXP_gr\FlashFXPPortable.exe

;Ctrl + Alt + P: 打开截图
!^p::Run, D:\WinSnapCHS\WinSnap 64.exe


;open Matlab
;#m::Run, D:\Matlab\bin\matlab.exe D:\Document\MATLAB

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Run Program
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Hotstring：热字符串-网站
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;在大多数软件输入"//b",然后回车就可以打开百度
;;百度
:://b::
Run, www.baidu.com
Return

;;在大多数软件输入"//b",然后回车就可以打开谷歌
;;谷歌
:://g::
Run, www.google.com.hk
Return

;;在大多数软件输入"//z",然后回车就可以打开知乎
;;知乎
:://z::
Run, www.zhihu.com
Return

;;在大多数软件输入"//w",然后回车就可以打开新浪微博
;;新浪微博
:://w::
Run, http://weibo.com
Return

;;在大多数软件输入"//wx",然后回车就可以打开微信网页版
;;微信网页版
:://wx::
Run, https://wx.qq.com/
Return

;;在大多数软件输入"//r",然后回车就可以打开睿思
;;睿思
:://r::
Run, http://rs.xidian.edu.cn/
Return

;;在大多数软件输入"//y",然后回车就可以打开网页印象笔记
;;印象笔记网页
:://y::
Run, https://app.yinxiang.com/Home.action#st=p
Return


;;在大多数软件输入"//mz",然后回车就可以打开个人博客
;;个人博客
:://mz::
Run, http://muzichao.com/
Return

;;在大多数软件输入"//ahk",然后回车就可以打开autohotkey 配置文件
;;打开autohotkey 配置文件
:://ahk::
Run, C:\Users\Administrator\Documents\AutoHotkey.ahk
return
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Hotstring：热字符串-网站
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Hotstring：热字符串-字符串
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;在大多数软件输入"//gm"，然后回车，自动输入gmail
:://gm::
Send, chaoli.xidian@gmail.com
Return

;;在大多数软件输入"//qm"，然后回车，自动输入腾讯邮箱
:://qm::
Send, 568191222@qq.com
Return

;;在大多数软件输入"//xm"，然后回车，自动输入西电邮箱
:://xm::
Send, chli@stu.xidian.edu.cn
Return

;;在大多数软件输入"//xm"，然后回车，自动输入西电邮箱
::gh::
Send, https://github.com/muzichao/
Return
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Hotstring：热字符串-字符串
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;文本操作快捷键
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;Vim Key Binding
#if ( A_Cursor = "IBeam" or A_CaretX >= 100 )
{
    ;Alt + a ：选择光标所在文本的一行
    !a::
    Send {Home}
    Send +{End}

    return

    ;Alt + c ：选择光标所在文本的一行，并复制
    !c::
    Send {Home}
    Send +{End}

    Send ^c
    return

    ;Alt + x ：选择光标所在文本的一行，并剪切
    !x::
    Send {Home}
    Send +{End}

    Send ^x
    return

    ;Alt + v ：粘贴并保存，同Ctrl+v,然后Ctrl+s保存
    !v::
    Send ^v
    Send ^s
    return

    ;Alt + n ：光标移动到行尾，并回车
    !n::
    Send {End}
    Send {Enter}
    return

    ;选择当前位置到行首的文字
    !y:: Send +{Home}
    Return

    ;选择当前位置到行末的文字
    !p:: Send +{End}
    Return

    ;跳转到当前位置的行首
    !u:: Send {Home}
    Return

    ;跳转到当前位置的行末
    !o:: Send {End}
    Return

    ;Alt + jkli 实现对方向键的映射,写代码的时候灰常有用
    ;Alt + i ：上键
    ;Alt + j ：左键
    ;Alt + k ：下键
    ;Alt + l ：右键
    !j::
    Send {left}
    Return

    !l::
    Send {right}
    Return

    !i:: Send {up}
    Return

    !k:: Send {down}
    Return


    ;Delete Backspace的映射
    ;Alt + d ：相当于Delete
    !d::
    Send {Delete}
    Send, {Enter}
    Return
}
#if



;Ctrl + 空格 映射为四个空格
;方便markdown语法中的使用
^Space::
Send, {Space}
Send, {Space}
Send, {Space}
Send, {Space}
Return

;Ctrl + 3(#) 映射为四个#
;方便markdown语法中的使用
^3::
Send, {#}
Send, {#}
Send, {#}
Send, {#}
Return

;Alt + ` 选中的文本两侧添加‘`’
;方便markdown语法中的使用
!`::
Send ^c
Sleep, 100
Send, ````
Send, {left}
Send, ^v
Send, {Right}
Return

;
;^b::
;Send ^v
;Sleep, 100
;Send {RButton}
;Send z
;Return

;^n::
;Send ^a
;Send 0.05
;Send {Enter}
;Return



;^b::
;Send {RButton}
;Send I
;Return

;^n::
;Send ^a
;Send 40
;Send {Enter}
;Return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;文本操作快捷键
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;小工具快捷键
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Alt + t : 25分钟计时-番茄钟
!t::
MsgBox 25 mins - Timing begins
;弹出一个对话框，上面显示着“Timing begins”。
Sleep, 25*60*1000
;Sleep 命令，很好理解，就是时间暂停，这句会暂停 360000 个千分之一秒，也就是 360000/1000 = 360 秒 = 6 分钟。
;这句也可以写成 Sleep 360000，就是把逗号改为空格。
MsgBox 25 mins - Timing over
;然后提示“Timing over”
return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;小工具快捷键
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;默认配置
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;打开网站
;#z::Run www.autohotkey.com

;;ctrl + alt + n：如果存成未命名的记事本，则打开，否则重新打开一个
^!n::
IfWinExist Untitled - Notepad
	WinActivate
else
	Run Notepad
return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;默认配置
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Note: From now on whenever you run AutoHotkey directly, this script
; will be loaded.  So feel free to customize it to suit your needs.

; Please read the QUICK-START TUTORIAL near the top of the help file.
; It explains how to perform common automation tasks such as sending
; keystrokes and mouse clicks.  It also explains more about hotkeys.
