#include "stack.h"

namespace wltr
{

    class VoidStack::StackImpl : public BaseStack
    {
    public:
        StackImpl();
        StackImpl(const StackImpl & other);
        StackImpl(StackImpl && other);
        StackImpl(std::vector<const void *> list, size_t data_size);
        ~StackImpl();

        StackImpl & operator = (const StackImpl & other);
        StackImpl & operator = (StackImpl && other);

        void push(const void * data, size_t data_size);
        void onTop(void * adress) const;
        void pop();
        bool isEmpty() const;

        Data &asteriscImpl(void *pointer) const ;
        void nextImpl(void *&pointer) const;
        void rangednextImpl(void *&pointer, int num) const;
        void rangedpreviousImpl(void *&pointer, int num) const;
        void previousImpl(void *&pointer) const;
        void *beginImpl() const;
        void findImpl(const Data &value, void *&pointer) const;
        void insertImpl(const Data &value, void *&pointer);
        void eraseImpl(void *&pointer);
        void clear();
        void copy(const BaseStack *) {}

        size_t _size;

    private:
        struct Node
        {
            void *data;
            size_t data_size;
            Node * next;
            Node * parent;
            Node() = default;
            Node(const void * adress, size_t data_size);
            Node(Node && other) = default;
            ~Node();
        } * top;

        void copy(Node *& top, Node * other_top);
        void swap(Node *& top, Node * other_top);
    };


    VoidStack::StackImpl::Node::Node(const void *adress, size_t data_size):data(nullptr),
                                                                           data_size(data_size),
                                                                           next(nullptr),
                                                                           parent(nullptr)
    {

        if(adress && data_size)
        {
            data = (void *)(new unsigned char[data_size]);

            for(size_t i = 0; i < data_size; ++i)
            {
                *((unsigned char *)data + i) = *((unsigned char *)adress + i);
            }
        }
    }

    VoidStack::StackImpl::Node::~Node()
    {
        if(data && data_size)
        {
            for(size_t j = 0; j < data_size; ++j)
            {
                *((unsigned char *) data + j) = 0;
            }

            data_size = 0;
            next = nullptr;

            delete [] data;
            data = nullptr;
        }
    }

    VoidStack::StackImpl::StackImpl():_size(0), top(nullptr) {}

    VoidStack::StackImpl::StackImpl(const StackImpl &other):_size(other._size), top(nullptr)
    {
        copy(top, other.top);
    }

    VoidStack::StackImpl::StackImpl(StackImpl &&other):_size(other._size), top(nullptr)
    {
        swap(top, other.top);
    }

    VoidStack::StackImpl::StackImpl(std::vector<const void *> list, size_t data_size):_size(list.size()), top(nullptr)
    {
        std::vector<const void *>::iterator it = list.begin();

        for(; it != list.end(); ++it)
        {
            push(*it, data_size);
        }
    }

    VoidStack::StackImpl::~StackImpl()
    {
        clear();
    }

    VoidStack::StackImpl & VoidStack::StackImpl::operator = (const VoidStack::StackImpl & other)
    {
        if(this != &other)
        {
            copy(top, other.top);
        }
        return * this;
    }

    VoidStack::StackImpl & VoidStack::StackImpl::operator = (VoidStack::StackImpl && other)
    {
        swap(top, other.top);
        return * this;
    }

    void VoidStack::StackImpl::swap(Node *& top, Node * other_top)
    {
        if(other_top == nullptr)
        {
            other_top = top;
        }
        else
        {
            std::swap(top, other_top);
            swap(top->next, other_top->next);
        }
    }

    void VoidStack::StackImpl::copy(Node *& top, Node * other_top)
    {
        Node * p = nullptr;

        while(other_top)
        {
            Node * r = nullptr;

            r = new Node(other_top->data, other_top->data_size);

            r->next = p;
            p = r;
            other_top = other_top->next;
        }

        while(p)
        {
            Node * r = p;
            r = p->next;
            p->next = other_top;
            other_top = p;
            p = r;
            r = nullptr;
        }

        top = other_top;
        other_top = nullptr;
    }

    void VoidStack::StackImpl::clear()
    {
        while(top)
        {
            Node * p = top;
            top = top->next;

            delete p;

            p = nullptr;
        }
    }

    void VoidStack::StackImpl::push(const void *data, size_t data_size)
    {
        Node * p = nullptr;

        p = new Node(data, data_size);
        if(top)
            top->parent = p;
        p->next = top;
        top = p;
        p = nullptr;

        ++_size;
    }

    void VoidStack::StackImpl::pop()
    {
        Node * p = top;

        if(p)
        {
            if(top->next)
                top->next->parent = nullptr;
            top = top->next;

            delete p;

            p = nullptr;

            --_size;
        }
    }

    void VoidStack::StackImpl::onTop(void *adress) const
    {
        if(top)
        {
            for(size_t i = 0; i < top->data_size; ++i)
            {
                *((unsigned char *) adress + i) =
                        *((unsigned char *) top->data + i);
            }
        }
        else throw StackException();
    }

    bool VoidStack::StackImpl::isEmpty() const
    {
        return top == nullptr;
    }


    /** Iterator compability Implementation */
    Data &VoidStack::StackImpl::asteriscImpl(void * pointer) const
    {
        if(pointer)
        {
            Node * tmp = (Node *)pointer;
            return tmp->data;
        }
        else throw StackException();
    }

    void VoidStack::StackImpl::nextImpl(void *&pointer) const
    {
        Node * current = (Node *)pointer;

        if(current)
        {
            current = current->next;
            pointer = (void *)current;
        }
    }

    void VoidStack::StackImpl::rangednextImpl(void *&pointer, int num) const
    {
        if(num < 0)
            throw StackException("Out of range!");

        Node * p = top;
        for(int i = 0; i < num; ++i)
        {
            if(p->next)
            {
                p = p->next;
            }
            else
                throw StackException("Out of range!");
        }

        pointer = (void *)p;
    }

    void VoidStack::StackImpl::rangedpreviousImpl(void *&pointer, int num) const
    {
        Node * p = top;
        while(p->next)
        {
            p = p->next;
        }

        for(int i = 0; i < num; ++i)
        {
            if(p->parent)
            {
                p = p->parent;
            }
            else
                throw StackException("Out of range!");
        }
    }

    void VoidStack::StackImpl::previousImpl(void *&pointer) const
    {
        Node * current = (Node *)pointer;

        if(current)
        {
            current = current->parent;
            pointer = (void *)current;
        }
    }

    void * VoidStack::StackImpl::beginImpl() const
    {
        Node * current = top;
        return (void *)current;
    }

    void VoidStack::StackImpl::findImpl(const Data &value, void *&pointer) const
    {
        Node * current = top;
        int i = 0;
        while(current && static_cast<unsigned char *>(value) !=
              static_cast<unsigned char *>(current->data))
        {
            current = current->next;
        }
        pointer = (void *)current;
    }

    void VoidStack::StackImpl::insertImpl(const Data &value, void *&pointer)
    {
        Node * current = nullptr;

        if(top)
        {
            current = new Node(value, top->data_size);
            top->parent = current;
            current->next = top;
            top = current;

            delete current;
            current = nullptr;
        }
        else
        {
            current = new Node(value, top->data_size);
            top = current;

            delete current;
            current = nullptr;
        }
        pointer = (void *)current;
    }

    void VoidStack::StackImpl::eraseImpl(void *&pointer)
    {
        if(pointer)
        {
            Node * current = (Node *)pointer;

            if(current == top)
            {
                pop();
            }
            else
            {
                current->parent->next = current->next;
                current->next->parent = current->parent;
                delete current;
                current = nullptr;
            }
        }
    }




    /** Second pimpl implementation  */
    VoidStack::VoidStack():pimpl(nullptr)
    {
        pimpl = new StackImpl;
    }

    VoidStack::VoidStack(const VoidStack &other):pimpl(nullptr)
    {
        pimpl = new StackImpl(*other.pimpl);
    }

    VoidStack::VoidStack(VoidStack &&other):pimpl(nullptr)
    {
        std::swap(pimpl, other.pimpl);
    }

    VoidStack::VoidStack(std::vector<const void *> list, int data_size):pimpl(nullptr)
    {
        pimpl = new StackImpl(list, data_size);
    }

    VoidStack::~VoidStack()
    {
        pimpl->clear();
        delete pimpl;
        pimpl = nullptr;
    }

    VoidStack & VoidStack::operator = (const VoidStack & other)
    {
        if(this != &other)
        {
            *pimpl = *other.pimpl;
        }
        return * this;
    }

    VoidStack & VoidStack::operator = (VoidStack && other)
    {
        *pimpl = std::move(*other.pimpl);
        return * this;
    }

    void VoidStack::push(const void *data, size_t data_size)
    {
        pimpl->push(data, data_size);
    }

    void VoidStack::pop()
    {
        pimpl->pop();
    }

    void VoidStack::onTop(void *adress) const
    {
        pimpl->onTop(adress);
    }

    bool VoidStack::isEmpty() const
    {
        return pimpl->isEmpty();
    }

    void VoidStack::clear()
    {
        pimpl->clear();
    }

    StackIterator<void *> VoidStack::begin() const
    {
        return pimpl->begin();
    }

    StackIterator<void *> VoidStack::end() const
    {
        return pimpl->end();
    }

    size_t VoidStack::size() const
    {
        return pimpl->_size;
    }

}
