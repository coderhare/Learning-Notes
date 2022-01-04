## Singleton 单例模式

单例模式的特点：只提供唯一一个类的实例，具有全局变量的特点，在任何位置都可以通过接口获取到那个唯一实例；

具体运用场景：
1. 设备管理器，系统中可能有多个设备，但只有一个设备管理器，用于管理设备驱动；
2. 数据池，用于缓存数据的数据结构；

## C++单例实现

基础要点：
1. 全局只有一个实例：static特性，同时禁止用户自己声明并定义实例（把构造函数设为private)
2. 线程安全
3. 禁止赋值和拷贝
4. 用户通过接口获取实例： 使用static类成员函数












参考资料：
> https://www.baidu.com/link?url=YXB0EFLHRLAptvIGv4LGH4s5eJ6WEOOF-RqEU00-_tsJ2b0_ty-jVN-CMgQSsPrIxeIoOR-H8SnVX1E0pKs6Da&wd=&eqid=d946d8ce000170320000000661b1f79a