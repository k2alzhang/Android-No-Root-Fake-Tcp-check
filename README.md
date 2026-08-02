# Android-No-Root-Fake-Tcp-check
Generate a dummy empty file to ensure that certain software in the Termux root container successfully passes port detection.    
生成一个伪装的空文件，让termux proot容器里面某些软件的端口检测成功通过

# 原理
在termux poroot环境里面，一些软件需要读取`/proc/net/tcp`(ipv4)和`/proc/net/tcp6`(ipv6)环境里面的端口，但没有su的情况下，proot环境无法读取这两个软件，会出现权限拒绝的情况，所以这个就是创建一个伪装文件引导软件通过端口环境检测

# 生成文件所使用的编程语言
我们使用c语言来生成相关的空伪装文件来绕过相关端口检测的文件

# 如何安装
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
等出现两个二进制文件之后，就成功了

# 说明
这只是一个思路型文件，开始的目的是用于布吉岛的某个脱盒系统上因为需要root检测端口的情况，为非root的安卓用户准备的
这是转载仓库，原作者不是我，但本人已经明确取得原作者同意进行转载

# B站原作者视频
![](https://www.bilibili.com/video/BV1nVGc6iExD?buvid=XX2911923AA46EE67964C1283E51D9908E621&from_spmid=main.space-contribution.0.0&is_story_h5=false&mid=1vS8YksZmjtAH5%2Bq2iuW138FTQ%2FSZMtL1rElX6M3iMo%3D&plat_id=116&share_from=ugc&share_medium=android&share_plat=android&share_session_id=94124ebd-62ae-4f77-846f-6a6baa5f9bd3&share_source=COPY&share_tag=s_i&spmid=united.player-video-detail.0.0&timestamp=1785673388&unique_k=yrrCq7W&up_id=1880806876)
