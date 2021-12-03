//
// Created by Morisummer on 2021/12/2.
//

#include <bits/stdc++.h>
#include "MySharedPtr.h"
using namespace std;



int main(){
    int * p = new int(0);
    MySharedPtr<int> ptr(p);
    ptr = ptr;
    //Test Copy constructor
    MySharedPtr<int> ptr2(ptr);
    MySharedPtr<int> ptr3(new int (1));
    ptr3 = ptr;
    return 0;
}
