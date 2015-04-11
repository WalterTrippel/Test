#ifndef STACK
#define STACK

#include "basestack.h"

namespace wltr
{
    class StackException : public std::exception
    {
    private:
        std::string ex;
    public:
        StackException() {ex = std::string("Stack Exception occured!");}
        StackException(std::string ex) {this->ex = std::string(ex);}

        const char * what() const throw()
        {
            return ex.c_str();
        }
    };


    class VoidStack;

    template<typename T>
    class Stack
    {
    public:

        typedef StackIterator<T> Iterator;

        Stack();
        Stack(const Stack & other);
        Stack(Stack && other);
        Stack(std::initializer_list<T> list);

        Stack & operator = (const Stack & other);
        Stack & operator = (Stack && other);

        virtual ~Stack();

        void push(T data);
        T onTop() const;
        void pop();
        bool isEmpty() const;
        void clear();

        size_t size() const;

        Iterator begin() const;
        Iterator end() const;

    private:
        VoidStack * pimpl;

    };

    class VoidStack
    {
    public:
        typedef StackIterator<void *> Iterator;

        VoidStack();
        VoidStack(const VoidStack & other);
        VoidStack(VoidStack && other);
        VoidStack(std::vector<const void *> vec, int data_size);

        VoidStack & operator = (const VoidStack & other);
        VoidStack & operator = (VoidStack && other);

        ~VoidStack();

        void push(const void * data, size_t data_size);
        void pop();
        void onTop(void * adress) const;
        bool isEmpty() const;
        void clear();

        size_t size() const;

        Iterator begin() const;
        Iterator end() const;

    private:
        class StackImpl;
        StackImpl * pimpl;
    };

    template<typename T>
    Stack<T>::Stack():pimpl(nullptr)
    {
        pimpl = new VoidStack;
    }

    template<typename T>
    Stack<T>::Stack(const Stack<T> & other):pimpl(nullptr)
    {
        pimpl = new VoidStack(*other.pimpl);
    }

    template<typename T>
    Stack<T>::Stack(Stack && other):pimpl(nullptr)
    {
        std::swap(pimpl, other.pimpl);
    }

    template<typename T>
    Stack<T>::Stack(std::initializer_list<T> list):pimpl(nullptr)
    {
        std::vector<const void *> vec;

        for(T i : list)
        {
            vec.push_back((void *)&i);
        }

        pimpl = new VoidStack(vec, sizeof(T));
    }

    template<typename T>
    Stack<T> & Stack<T>::operator = (const Stack<T> & other)
    {
        if(this != &other)
        {
            *pimpl = *other.pimpl;
        }
        return * this;
    }

    template<typename T>
    Stack<T> & Stack<T>::operator = (Stack<T> && other)
    {
        *pimpl = std::move(*other.pimpl);
    }

    template<typename T>
    Stack<T>::~Stack()
    {
        pimpl->clear();
        delete pimpl;
        pimpl = nullptr;
    }

    template<typename T>
    void Stack<T>::push(T data)
    {
        pimpl->push((void *)&data, sizeof(T));
    }

    template<typename T>
    void Stack<T>::pop()
    {
        pimpl->pop();
    }

    template<typename T>
    bool Stack<T>::isEmpty() const
    {
        return pimpl->isEmpty();
    }

    template<typename T>
    void Stack<T>::clear()
    {
        pimpl->clear();
    }

    template<typename T>
    T Stack<T>::onTop() const
    {
        unsigned char *bufer = new unsigned char[sizeof(T)];
      pimpl->onTop((void *) bufer);
      return *((T *)bufer);
    }

    template<typename T>
    size_t Stack<T>::size() const
    {
        return pimpl->size();
    }

    template<typename T>
    StackIterator<T> Stack<T>::begin() const
    {
        StackIterator<void *> tmp = pimpl->begin();
        return *(StackIterator<T> *)&tmp;
    }

    template<typename T>
    StackIterator<T> Stack<T>::end() const
    {
        StackIterator<void *> tmp = pimpl->end();
        return *(StackIterator<T> *)&tmp;
    }

}

#endif // STACK

