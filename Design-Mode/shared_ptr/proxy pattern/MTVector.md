使用代理模式，由代理对象提供对原有对象的访问
这里设计了一个支持线程安全的vector
```c++
template<class T>
class MTvector{
    vector <T> arr;
    shared_mutex m_mtx; //shared_mutex既可以共享也可以不共享
public:
    void push_back(T i){
        m_mtx.lock();
        arr.push_back(i);
        m_mtx.unlock();
    }
    size_t size() const{
        m_mtx.lock_shared();
        size_t sz = arr.size();
        m_mtx.unlock_shared();
        return sz;
    }
};
```