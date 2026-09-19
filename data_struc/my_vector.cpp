#include <memory>
#include <initializer_list>
/** 
    *@note: this is the linear array data structure,I wrote it to practice the 
    *       knowledge of the class copy control in the c plus plus
    *@note: std::move(x) return a left value of the parameter x,after using std::move,you can 
    *assign value to x,or delete x,but you can't using x's old value.
    *@note: don't write using std::move;
*/
template<typename T>
class MyVector
{
    private:
        class Iterator;
        class const_Iterator;
    public:
        MyVector(size_t size = 0, size_t capacity = 10):size(size),capacity(capacity){}
        MyVector(std::initializer_list<T> list);//lsit initialize
        MyVector(const MyVector<T>& copy);
        MyVector(MyVector<T>&& copy) noexcept;
        MyVector<T>& operator=(const MyVector<T>& copy);
        MyVector<T>& operator=(MyVector<T>&& copy)& noexcept;
        ~MyVector();
        void push_back(const T& value);
        void push_back(T&& value);
        Iterator begin()const;
        Iterator end()const;
        const_Iterator cbegin() const;
        const_Iterator cend() const;
    private:
        T* head = nullptr;
        size_t size;
        size_t capacity;
        std::allocator<T> alloc_controller;
};


template<class T>
MyVector<T>::MyVector(std::initializer_list<T> list)
{
    size = list.size();
    capacity = size * 2;
    head = alloc_controller.allocate(capacity);
    std::uninitialized_copy(std::make_move_iterator(list.begin()),std::make_move_iterator(list.end()),head);        
}

template<class T>
MyVector<T>::MyVector(const MyVector<T>& copy)
{
    size = copy.size;
    capacity = copy.capacity;
    head = alloc_controller.allocate(capacity);
    std::uninitialized_copy(copy.head,copy.head+size,head);
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& copy)
{
    if(this == &copy)
        return *this;

    if(capacity < 2 * copy.size)
    {
        for(size_t i = 0;i < size;i++)
        {
            alloc_controller.destroy(head+i);
        }
        head = alloc_controller.allocate(copy.capacity);
        capacity = copy.capacity;
    }

    std::uninitialized_copy(copy.head,copy.head+copy.size,head);
    size = copy.size;
    return *this;    
}

template<class T>
MyVector<T>::MyVector(MyVector<T>&& copy) noexcept
{
    head = copy.head; size = copy.size; capacity = copy.capacity;
    copy.head = nullptr; copy.size = 0;copy.capacity = 0;
}
template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& copy)& noexcept
{
    if(this == &copy)
        return *this;

    head = copy.head; size = copy.size; capacity = copy.capacity;
    copy.head = nullptr; copy.size = 0;copy.capacity = 0;
    return *this;
}

template<class T>
MyVector<T>::~MyVector()
{
    for(size_t i = 0;i < size;i++)
        alloc_controller.destroy(head+i);
    alloc_controller.deallocate(head,capacity);
}

template<class T>
void MyVector<T>::push_back(const T& value)
{
    if(capacity < 2*(size+1))
    {
        for(size_t i = 0;i < size;i++)
        {
            alloc_controller.destroy(head+i);
        }
        head = alloc_controller.allocate(capacity*2);
        capacity*=2;
    }
    alloc_controller.construct(head+size,value);
    size++;
}

template<class T>
void MyVector<T>::push_back(T&& value)
{
     if(capacity < 2*(size+1))
     {
        for(size_t i = 0;i < size;i++)
        {
            alloc_controller.destroy(head+i);
        }
        head = alloc_controller.allocate(2*capacity);
        capacity = 2*capacity;
    }
    alloc_controller.construct(head+size,value);
    size++;
}
//no meaning to use move here




template<class T>
class MyVector<T>::Iterator
{
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;   

        Iterator(T* position):position(position){}
        Iterator(const Iterator& copy){position = copy.position;}
        Iteratpr(Iterator&& move) = delete;
        ~Iterator(){position = nullptr;}
        Iterator& operator=(const Iterator& copy){position = copy.position;}
        Iterator& operator=(Iterator&& move) = delete;
        T& operator*(){return *position;}
        T& operator++(){T& temp = *position;position++;return temp;}
        T& operator++(int){position++;return *position;}
        T& operator--(){T& temp = *position;position--;return temp;}
        T& operator--(int){return *(--position);}
        Iterator operator+(int n){return Iterator(position+n);}
        Iterator operator-(int n){return Iterator(position-n);}
        T& operator[](int n){return position[n];}
        bool operator>(Iterator it2){return position > it2.position;}
        bool operator<(Iterator it2){return position < it2.position;}
        bool operator==(Iterator it2){return position == it2.position;}
    private:
        T* position;

};
template<class T>
class MyVector<T>::const_Iterator
{

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;   

        const_Iterator(T* position):position(position){}
        const_Iterator(const Iterator& copy){position = copy.position;}
        const_Iterator(Iterator&& move) = delete;
        ~const_Iterator(){position = nullptr;}
        Iterator& operator=(const Iterator& copy){position = copy.position;}
        Iterator& operator=(Iterator&& move) = delete;
        T& operator*(){return *position;}
        T& operator++(){T& temp = *position;position++;return temp;}
        T& operator++(int){position++;return *position;}
        T& operator--(){T& temp = *position;position--;return temp;}
        T& operator--(int){return *(--position);}
        Iterator operator+(int n){return Iterator(position+n);}
        Iterator operator-(int n){return Iterator(position-n);}
        T& operator[](int n){return position[n];}
        bool operator>(Iterator it2){return position > it2.position;}
        bool operator<(Iterator it2){return position < it2.position;}
    private:
        const T* position;
};

template<class T>
typename  MyVector<T>::Iterator MyVector<T>::begin()const
{
    return Iterator(head);
}

template<class T>
typename MyVector<T>::Iterator MyVector<T>::end()const
{
    return Iterator(head+size);
}



template<class T>
typename MyVector<T>::const_Iterator MyVector<T>::cbegin()const
{
    return Iterator(head);
}
template<class T>
typename MyVector<T>::const_Iterator MyVector<T>::cend()const
{
    return Iterator(head+size);
}