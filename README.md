# Android-No-Root-Fake-Tcp-check
Generate a dummy empty file to ensure that certain software in the Termux root container successfully passes port detection.    
生成一个伪装的空文件，让termux proot容器里面某些软件的端口检测成功通过

## 原理
在termux poroot环境里面，一些软件需要读取`/proc/net/tcp`(ipv4)和`/proc/net/tcp6`(ipv6)环境里面的端口，但没有su的情况下，proot环境无法读取这两个软件，会出现权限拒绝的情况，所以这个就是创建一个伪装文件引导软件通过端口环境检测

## 生成文件所使用的编程语言
我们使用c语言来生成相关的空伪装文件来绕过相关端口检测的文件

## 如何安装
termux首先先执行如下指令安装gcc
```
pkg install gcc
```

接着去release下载相关的c语言脚本，放在你知道的文件路径的文件夹里面

然后termux接着cd到相关文件夹下

接着运行如下指令
```
gcc -shared -fPIC -o fake_tcp.so fake_tcp.c -ldl
```
等出现两个二进制文件夹之后，就成功了

