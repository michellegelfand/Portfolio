#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__

namespace ilrd
{

template <typename T>
class SharedPtr
{
public:
    //Proper usage example:
    // SharedPtr<X> x1(new X);
    explicit SharedPtr(T* ptr = 0);

    template<typename Td>
    SharedPtr(const SharedPtr<Td>& other);
    ~SharedPtr();

    template<typename Td>
    SharedPtr& operator=(const SharedPtr<Td>& other);
    
    T& operator*() const;
    T* operator->() const;

    bool operator !() const;
    T* GetPtr();
    T* GetPtr() const;
    size_t *GetNumInstances() const;

private:
    std::size_t *m_num_of_instances;
    T *m_ptr;
};


template <typename T>
size_t* SharedPtr<T>::GetNumInstances() const
{
    return m_num_of_instances;
}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr)
    :m_ptr(ptr), m_num_of_instances(new size_t(1))
{
}

template<typename T>
T *SharedPtr<T>::GetPtr()
{
    return m_ptr;
}

template<typename T>
T *SharedPtr<T>::GetPtr() const
{
    return m_ptr;
}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    --*m_num_of_instances;
    
    if(!*m_num_of_instances)
    {
        delete m_num_of_instances;
        delete m_ptr;
    }
}

template<typename T>
template<typename Td>
SharedPtr<T>::SharedPtr(const SharedPtr<Td>& other)
   : m_ptr(other.m_ptr), m_num_of_instances(other.m_num_of_instances)
{
    ++(*m_num_of_instances);
}

template<typename T>
template<typename Td>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<Td>& other)
{
    SharedPtr::~SharedPtr();
    m_ptr = other.GetPtr();
    m_num_of_instances = other.GetNumInstances();
    ++(*m_num_of_instances);
    
    return *this;
}

template<typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}


template<typename T>
bool SharedPtr<T>::operator!() const
{
    return !m_ptr;
}


}//namespace ilrd
#endif //__SHAREDPTR_H__