#include "basestack.h"


/** Base Stack Implementation */
BaseStack::BaseStack() {}

BaseStack::BaseStack(const BaseStack & other)
{
    copy(&other);
}

BaseStack::~BaseStack()
{
    clear();
}

BaseStack::Iterator BaseStack::find(const Data &value) const
{
    void * pointer = nullptr;
    findImpl(value, pointer);
    return Iterator(this, pointer);
}

BaseStack::Iterator BaseStack::insert(const Data &value)
{
    void * pointer = nullptr;
    insertImpl(value, pointer);
    return Iterator(this, pointer);
}

BaseStack::Iterator BaseStack::erase(const Iterator &position)
{
    if(this !=  position.owner)
    {
        throw StackIteratorException();
    }

    void * pointer = position.current;
    eraseImpl(pointer);
    return StackIterator<Data>(this, pointer);
}

int BaseStack::erase(const Data &value)
{
    int counter = 0;
    void * pointer = nullptr;
    findImpl(value, pointer);

    while(pointer)
    {
        ++counter;
        eraseImpl(pointer);
        findImpl(value, pointer);
    }

    return counter;
}

BaseStack::Iterator BaseStack::begin() const
{
    return Iterator(this, beginImpl());
}

BaseStack::Iterator BaseStack::end() const
{
    return Iterator(this, 0);
}

Data & BaseStack::asterisc(void *pointer) const
{
    return asteriscImpl(pointer);
}

void BaseStack::next(void *&pointer) const
{
    nextImpl(pointer);
}

void BaseStack::previous(void *&pointer) const
{
    previousImpl(pointer);
}

void BaseStack::rangednext(void *&pointer, int num) const
{
    rangednextImpl(pointer, num);
}

void BaseStack::rangedprevious(void *&pointer, int num) const
{
    rangedpreviousImpl(pointer, num);
}

