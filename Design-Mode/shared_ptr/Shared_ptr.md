#Shared_Ptr
此代码为复现c++的智能指针shared_ptr的主体功能，实现原理为：使用一个引用计数型指针变量，
每次调用拷贝构造函数和赋值运算符都会触发计数器加1，当计数器为0时释放该资源