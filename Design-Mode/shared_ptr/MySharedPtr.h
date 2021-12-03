//
// Created by Morisummer on 2021/12/2.
//

#ifndef SHARED_PTR_MYSHAREDPTR_H
#define SHARED_PTR_MYSHAREDPTR_H

#endif //SHARED_PTR_MYSHAREDPTR_H

//实现原理：有一个引用计数型的指针变量，专门用于引用计数，当使用拷贝构造函数和赋值运算符时，引用计数+1，
//当引用计数为0时释放资源
#include <bits/stdc++.h>
using namespace std;

template <class T>
class MySharedPtr{
public:
    MySharedPtr(T * p = nullptr);
    ~MySharedPtr();
    MySharedPtr(const MySharedPtr & other);
    MySharedPtr<T> & operator=(const MySharedPtr<T> & other);
private:
    T * m_ptr;
    unsigned int * m_count; //RAII引用计数
};

template <class T>
MySharedPtr<T>::MySharedPtr(T *p) {
    m_ptr = p;
    m_count = new unsigned int(0);
    ++*(m_count);
    cout << "Constructor is succeed!\n";
}

template <class T>
MySharedPtr<T>::~MySharedPtr<T>() {
    --*(m_count);
    if(*m_count == 0){
        delete [] m_ptr;
        m_ptr = nullptr;
        delete [] m_count;
        m_count = nullptr;
        cout << "Destructor is succeed!\n";
    }
}

template <class T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<T> &other) {
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    ++(*m_count);
    cout << "Copy constructor is succeed!\n";
}

template <class T>
MySharedPtr<T> & MySharedPtr<T>::operator=(const MySharedPtr<T> &other) {
    //在减少左操作数的使用计数前先使other的使用计数+1
    //从而防止自身赋值
    ++(*other.m_count);
    --(*m_count);
    //将左操作数对象的使用计数-1，若该对象的使用计数减为0，则删除该对象
    if(*m_count == 0){
        delete[] m_ptr;
        m_ptr = nullptr;
        delete[] m_count;
        m_count = nullptr;
        cout << "Left side Object is deleted!\n";
    }
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    cout << "Assignment operator overloaded is succeed!\n";
    return *this;
}
