使用代理模式，由代理对象提供对原有对象的访问
这里设计了一个支持线程安全的vector
```c++
template<class T>
class MTvector{
    vector <T> arr;
    mutable mutex m_mtx; //mutable使得size()仍可为const，但是其实际上是可以非const
public:
    void push_back(T i){
        m_mtx.lock();
        arr.push_back(i);
        m_mtx.unlock();
    }
    size_t size() const{
        m_mtx.lock();
        size_t sz = arr.size();
        m_mtx.unlock();
        return sz;
    }
};
```