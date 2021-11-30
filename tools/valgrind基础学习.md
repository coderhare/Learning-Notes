# valgrind基础学习

> valgrind是一个Linux下的动态内存检测工具，其包括的几个功能可以帮助开发者发现使用中的内存泄漏情况

![img.png](Learning-Notes/images/img.png)

### valgrind包含的工具：

1. `memcheck`：检查程序中的内存问题，包括内存泄漏，数组越界，非法指针等
2. `callgrind`：检查程序代码覆盖，以及分析代码性能等
3. `Cachegrind`：分析CPU的cache命中率，丢失率，内存引用次数，代码产生的指令数等，用于进行代码优化
4. `helgrind`：用于检查多线程程序的竞争问题
5. `massif`：堆栈分析器，检查出程序在堆栈中用了多少内存，堆栈大小，以及管理堆栈等



### 用法：

可以先将c文件编译再进行检查

```shell
gcc -c test.c
gcc -o test.o
```
valgrind命令的参数较多,其中用法中`--tool=XXX`指定所使用的工具（见上文
```shell
valgrind --tool=memcheck --leak-check=full ./test
```







































参考： 

1. [Valgrind学习总结](https://blog.csdn.net/andylauren/article/details/93189740)
2. [Valgrind官网](https://valgrind.org/docs/manual/quick-start.html#quick-start.mcrun)

