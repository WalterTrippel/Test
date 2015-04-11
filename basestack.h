#ifndef BASESTACK_H
#define BASESTACK_H

#include <iostream>
#include <assert.h>
#include <vector>

typedef void * Data;

class StackIteratorException : public std::exception
{
    const char * what() const throw()
    {
        return "The iterator is not binded with container";
    }
};

template<typename T>
class StackIterator;

class BaseStack
{
public:
    typedef StackIterator<Data> Iterator;

    template<typename>
    friend class StackIterator;

    BaseStack();
    BaseStack(const BaseStack & other);
    ~BaseStack();

    Iterator find(const Data & value) const;
    Iterator insert(const Data & value);
    Iterator erase(const Iterator & position);
    int erase(const Data & value);
    Iterator begin() const;
    Iterator end() const;

private:

    Data &asterisc(void *pointer) const;
    void next(void *&pointer) const;
    void previous(void *&pointer) const;
    void rangednext(void *&pointer, int num) const;
    void rangedprevious(void *&pointer, int num) const;

    //Implementation
    virtual Data &asteriscImpl(void *pointer) const = 0;
    virtual void nextImpl(void *&pointer) const = 0;
    virtual void rangednextImpl(void *&pointer, int num) const = 0;
    virtual void rangedpreviousImpl(void *&pointer, int num) const = 0;
    virtual void previousImpl(void *&pointer) const = 0;
    virtual void *beginImpl() const = 0;
    virtual void findImpl(const Data &value, void *&pointer) const = 0;
    virtual void insertImpl(const Data &value, void *&pointer) = 0;
    virtual void eraseImpl(void *&pointer) = 0;
    virtual void clear() {}
    virtual void copy(const BaseStack *) {}
};

template<typename T>
class StackIterator
{
public:
    size_t next_counter;

    friend class BaseStack;
    StackIterator();
    ~StackIterator();

    T & operator*() const;
    StackIterator operator + (int num);
    StackIterator operator - (int num);
    StackIterator operator ++ ();
    StackIterator operator ++(int);

    StackIterator operator -- ();
    StackIterator operator --(int);

    bool operator == (const StackIterator &other) const;
    bool operator != (const StackIterator & other) const { return !(*this == other); }

private:
    const BaseStack * owner;
    void * current;

    StackIterator(const BaseStack * owner, void * current);
};

template<typename T>
StackIterator<T>::StackIterator():next_counter(0), owner(nullptr), current(nullptr) {}

template<typename T>
StackIterator<T>::~StackIterator()
{
    owner = nullptr;
    current = nullptr;
}

template<typename T>
T & StackIterator<T>::operator *() const
{
    if(owner)
        return *(T*)owner->asterisc(current);
    else
        throw StackIteratorException();
}

template<typename T>
StackIterator<T> StackIterator<T>::operator +(int num)
{
    if(owner)
    {
        owner->rangednext(current, num);
    }
    return *this;
}

template<typename T>
StackIterator<T> StackIterator<T>::operator -(int num)
{
    if(owner)
    {
        owner->rangedprevious(current, num);
    }
    return *this;
}

template<typename T>
StackIterator<T> StackIterator<T>::operator ++()
{
    if(owner)
    {
        owner->next(current);
    }
    return *this;
}

template<typename T>
StackIterator<T> StackIterator<T>::operator ++(int)
{
    StackIterator result(*this);

    ++(*this);
    return result;
}

template<typename T>
StackIterator<T> StackIterator<T>::operator --()
{
    if(owner)
    {
        owner->previous(current);
    }
    return * this;
}

template<typename T>
StackIterator<T> StackIterator<T>::operator --(int)
{
    StackIterator result(*this);

    --(*this);
    return result;
}

template<typename T>
bool StackIterator<T>::operator ==(const StackIterator<T> & other) const
{
    return owner == other.owner && current == other.current;
}

template<typename T>
StackIterator<T>::StackIterator(const BaseStack *owner, void *current):owner(owner), current(current) {}


#endif // BASESTACK_H
