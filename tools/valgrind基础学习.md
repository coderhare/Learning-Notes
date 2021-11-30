# valgrind基础学习

> valgrind是一个Linux下的动态内存检测工具，其包括的几个功能可以帮助开发者发现使用中的内存泄漏情况

![img.png](https://github.com/coderhare/Learning-Notes/blob/master/images/img.png)

### valgrind包含的工具：

1. `memcheck`：检查程序中的内存问题，包括内存泄漏，数组越界，非法指针等
2. `callgrind`：检查程序代码覆盖，以及分析代码性能等
3. `Cachegrind`：分析CPU的cache命中率，丢失率，内存引用次数，代码产生的指令数等，用于进行代码优化
4. `helgrind`：用于检查多线程程序的竞争问题
5. `massif`：堆栈分析器，检查出程序在堆栈中用了多少内存，堆栈大小，以及管理堆栈等



### 用法：

可以先将c文件编译再进行检查
```shell
gcc -o test test.c
```
用法：`valgrind [options] prog-and-args`

valgrind命令option的参数较多,其中用法中`--tool=XXX`指定所使用的工具（见上文
用法举例
```shell
valgrind --tool=memcheck --leak-check=full ./test
```
`leak-check=full`要求得到内存中泄漏的位置

### 实例分析：
`HEAP SUMMARY`统计了堆的使用情况，`LEAK SUMMARY`统计了内存泄漏的的情况，
`ERROR SUMMARY`统计了所有的错误情况，比方说：
`malloc/free`统计了退出时还有多少内存没有释放以及调用次数
```c++
[konten@tencent test_valgrind]$ valgrind --leak-check=full ./memleak
==29661== Memcheck, a memory error detector.
==29661== Copyright (C) 2002-2007, and GNU GPL'd, by Julian Seward et al.
==29661== Using LibVEX rev 1732, a library for dynamic binary translation.
==29661== Copyright (C) 2004-2007, and GNU GPL'd, by OpenWorks LLP.
==29661== Using valgrind-3.2.3, a dynamic binary instrumentation framework.
==29661== Copyright (C) 2000-2007, and GNU GPL'd, by Julian Seward et al.
==29661== For more details, rerun with: -v
==29661==
==29661==
==29661== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 15 from 1)
==29661== malloc/free: in use at exit: 10 bytes in 1 blocks.
==29661== malloc/free: 1 allocs, 0 frees, 10 bytes allocated.
==29661== For counts of detected errors, rerun with: -v
==29661== searching for pointers to 1 not-freed blocks.
==29661== checked 56,164 bytes.
==29661==
==29661== 10 bytes in 1 blocks are definitely lost in loss record 1 of 1
==29661==    at 0x401A846: malloc (vg_replace_malloc.c:149)
==29661==    by 0x804835D: main (memleak.c:6)
==29661==
==29661== LEAK SUMMARY:
==29661==    definitely lost: 10 bytes in 1 blocks.
==29661==      possibly lost: 0 bytes in 0 blocks.
==29661==    still reachable: 0 bytes in 0 blocks.
==29661==         suppressed: 0 bytes in 0 blocks.
[konten@tencent test_valgrind]$
```

#### 使用了未初始化的内存
```c++
#include <stdio.h>                                                              
int main()
{
    int x;
    if(x == 0)
    {
        printf("X is zero");
    }
    return 0;
}

Valgrind提示如下
==14222== Conditional jump or move depends on uninitialised value(s)
==14222== at 0x400484: main (sample2.c:6)
X is zero==14222==
==14222== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 5 from 1)
==14222== malloc/free: in use at exit: 0 bytes in 0 blocks.
==14222== malloc/free: 0 allocs, 0 frees, 0 bytes allocated.
==14222== For counts of detected errors, rerun with: -v
==14222== All heap blocks were freed -- no leaks are possible.
```

#### 读写越界
```c++
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
    int len=5;
    int i;
    int *pt=(int*)malloc(len*sizeof(int));
    int *p=pt;
    for(i=0;i<len;i++)
    {p++;}
    *p=5;
    printf("%d",*p);
    return;
}
Valgrind提示如下
==23045== Invalid write of size 4  //指示非法读写
==23045== at 0x40050A: main (sample2.c:11)
==23045== Address 0x4C2E044 is 0 bytes after a block of size 20 alloc'd
==23045== at 0x4A05809: malloc (vg_replace_malloc.c:149)
==23045== by 0x4004DF: main (sample2.c:7)
==23045==
==23045== Invalid read of size 4
==23045== at 0x400514: main (sample2.c:12)
==23045== Address 0x4C2E044 is 0 bytes after a block of size 20 alloc'd
==23045== at 0x4A05809: malloc (vg_replace_malloc.c:149)
==23045== by 0x4004DF: main (sample2.c:7)
5==23045==
==23045== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 5 from 1)
==23045== malloc/free: in use at exit: 20 bytes in 1 blocks.
==23045== malloc/free: 1 allocs, 0 frees, 20 bytes allocated.
==23045== For counts of detected errors, rerun with: -v
==23045== searching for pointers to 1 not-freed blocks.
==23045== checked 66,584 bytes.
==23045==
==23045== LEAK SUMMARY:
==23045== definitely lost: 20 bytes in 1 blocks.
==23045== possibly lost: 0 bytes in 0 blocks.
==23045== still reachable: 0 bytes in 0 blocks.
==23045== suppressed: 0 bytes in 0 blocks.
==23045== Use --leak-check=full to see details of leaked memory.
```

内存越界，数组越界，重复释放，非法指针等的综合分析
```c++
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    char *ptr = malloc(10);
    ptr[12] = 'a'; // 内存越界
    memcpy(ptr +1, ptr, 5); // 踩内存
    char a[10];
    a[12] = 'i'; // 数组越界
     free(ptr); // 重复释放
       free(ptr);
    char *p1;
    *p1 = '1'; // 非法指针
   
    return 0;
}
编译： gcc -o invalidptr invalidptr.c -g
执行：valgrind --leak-check=full ./invalidptr
结果如下：
[konten@tencent test_valgrind]$ valgrind --leak-check=full ./invalidptr
==29776== Memcheck, a memory error detector.
==29776== Copyright (C) 2002-2007, and GNU GPL'd, by Julian Seward et al.
==29776== Using LibVEX rev 1732, a library for dynamic binary translation.
==29776== Copyright (C) 2004-2007, and GNU GPL'd, by OpenWorks LLP.
==29776== Using valgrind-3.2.3, a dynamic binary instrumentation framework.
==29776== Copyright (C) 2000-2007, and GNU GPL'd, by Julian Seward et al.
==29776== For more details, rerun with: -v
==29776==
==29776== Invalid write of size 1 //堆内存越界被查出来
==29776==    at 0x80483D2: main (invalidptr.c:7)
==29776== Address 0x4159034 is 2 bytes after a block of size 10 alloc'd
==29776==    at 0x401A846: malloc (vg_replace_malloc.c:149)
==29776==    by 0x80483C5: main (invalidptr.c:6)
==29776==
==29776== Source and destination overlap in memcpy(0x4159029, 0x4159028, 5) //踩内存
==29776==    at 0x401C96D: memcpy (mc_replace_strmem.c:116)
==29776==    by 0x80483E6: main (invalidptr.c:9)
==29776==
==29776== Invalid free() / delete / delete[] //重复释放
==29776==    at 0x401B3FB: free (vg_replace_malloc.c:233)
==29776==    by 0x8048406: main (invalidptr.c:16)
==29776== Address 0x4159028 is 0 bytes inside a block of size 10 free'd
==29776==    at 0x401B3FB: free (vg_replace_malloc.c:233)
==29776==    by 0x80483F8: main (invalidptr.c:15)
==29776==
==29776== Use of uninitialised value of size 4
==29776==    at 0x804840D: main (invalidptr.c:19)
==29776== //非法指针，导致coredump
==29776== Process terminating with default action of signal 11 (SIGSEGV): dumping core
==29776== Bad permissions for mapped region at address 0x80482AD
==29776==    at 0x804840D: main (invalidptr.c:19)
==29776==
==29776== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 15 from 1)
==29776== malloc/free: in use at exit: 0 bytes in 0 blocks.
==29776== malloc/free: 1 allocs, 2 frees, 10 bytes allocated.
==29776== For counts of detected errors, rerun with: -v
==29776== All heap blocks were freed -- no leaks are possible.
Segmentation fault
[konten@tencent test_valgrind]$
```

































参考： 

1. [Valgrind学习总结](https://blog.csdn.net/andylauren/article/details/93189740)
2. [Valgrind官网](https://valgrind.org/docs/manual/quick-start.html#quick-start.mcrun)
3. [Valgrind例子](https://www.cnblogs.com/freedomabcd/p/7771551.html)