多线程 http get 发包工具

编译: gcc get.c -pthread -o getdos

使用方法: 

$ ./getdos "url" thread

$ ./getdos "网址" 线程

例子:

$ ./getdos "http://www.xxx.com/new.php?id=5&p=5" 10

网址里面如果含&必须加双引号，线程可不填，默认线程5



这个是我花了几天时间一边学习一边写的一个小程序，算是我写的第一个比较有用的程序，学到了很多东西。很开心。我是新手，欢迎批评 ^_^
