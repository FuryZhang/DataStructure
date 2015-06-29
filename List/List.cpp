#include "List.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

/*template <typename Object>
struct List<Object>::Node
{
    Object data;
    Node *prev;
    Node *next;

    Node(const Object &d = Object(), Node *p = nullptr, Node *n = nullptr)
        : data(d), prev(p), next(n) {}
};*/

template <typename Object>
class List<Object>::const_iterator
{
public:
    const_iterator() : the_list_(nullptr), current_(nullptr) {}

    const Object& operator* () const
    {
        return retrieve();
    }

    const_iterator& operator++ ()
    {
        current_ = current_->next;
        return *this;
    }

    const_iterator operator++ (int)
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }

    bool operator== (const const_iterator &rhs) const
    {
        return the_list_ == rhs.the_list_ && current_ == rhs.current_;
    }

    bool operator!= (const const_iterator &rhs) const
    {
        return !(*this == rhs);
    }

protected:
    const List<Object> *the_list_;
    Node *current_;

    Object& retrieve() const
    {
        return current_->data;
    }

    const_iterator(const List<Object> &list, Node *p) : the_list_(&list), current_(p) {}

    void assert_is_valid() const
    {
        if (!the_list_ || !current_ || current_ == the_list_->head_)
        {
//            throw IteratorOutOfBoundsException();
        }
    }

    friend class List<Object>;
};

template <typename Object>
class List<Object>::iterator : public const_iterator
{
public:
    iterator() {}

    Object& operator* ()
    {
        return retrieve();
    }

    const Object& operator* () const
    {
        return const_iterator::operator*();
    }

    iterator& operator++ ()
    {
        current_ = current_->next;
        return *this;
    }

    iterator operator++ (int)
    {
        iterator old = *this;
        ++(*this);
        return old;
    }

protected:
    iterator(const List<Object> &list, Node *p) : const_iterator(list, p) {}

    friend class List<Object>;
};

template <typename Object>
List<Object>::List()
{
    init();
}

template <typename Object>
List<Object>::List(const List& rhs)
{
    init();
    *this = rhs;
}

template <typename Object>
List<Object>::~List()
{
    clear();
    delete head_;
    delete tail_;
}

template <typename Object>
const List<Object>& List<Object>::operator=(const List& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    clear();
    for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
    {
        push_back(*iter);
    }

    return *this;
}

template <typename Object>
typename List<Object>::iterator List<Object>::insert(iterator iter, const Object& x)
{
    iter.assert_is_valid();
    if (iter.the_list_ != this)
    {
//        throw IteratorMismatchException();
    }

    Node *p = iter.current_;
    the_size_++;
    return iterator(*this, p->prev = p->prev->next = new Node(x, p->prev, p)); // 返回要加入结点的迭代器
    /*// 上面一句等同下面
    Node *newNode = new Node(x, p->prev, p);
    p->prev->next = newNode;
    p->prev = newNode;*/
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator iter)
{
    Node *p = iter.current_;
    iterator ret_val(*this, p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    the_size_--;

    return ret_val; // 返回删除结点的下个结点的迭代器
}

template <typename Object>
typename List<Object>::iterator List<Object>::erase(iterator start, iterator end)
{
    for (iterator iter = start; iter != end;)
    {
        iter = iter.erase(iter);
    }

    return end;
}

template <typename Object>
void List<Object>::init()
{
    the_size_ = 0;
    head_ = new Node;
    tail_ = new Node;
    head_->next = tail_;
    tail_->prev = head_;
}

int main()
{
    List<int> testList;
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 10; ++i)
    {
        testList.push_back(rand() % 100);
    }
    testList.insert(testList.end(), 99);
    for (List<int>::const_iterator it = testList.begin(); it != testList.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
}