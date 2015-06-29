#ifndef DATASTRUCTURE_LIST_H_
#define DATASTRUCTURE_LIST_H_

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object(), Node *p = nullptr, Node *n = nullptr)
            : data(d), prev(p), next(n) {}
    };

public:
    class const_iterator;
    class iterator;

public:
    List();
    List(const List &rhs);
    ~List();

    const List& operator=(const List &rhs);

    iterator begin()
    {
        return iterator(*this, head_->next);
    }

    const_iterator begin() const
    {
        return const_iterator(*this, head_->next);
    }

    iterator end()
    {
        return iterator(*this, tail_);
    }

    const_iterator end() const
    {
        return const_iterator(*this, tail_);
    }

    int size() const
    {
        return the_size_;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    Object& front()
    {
        return *begin();
    }

    const Object& front() const
    {
        return *begin();
    }

    Object& back()
    {
        return *--end();
    }

    const Object& back() const
    {
        return *--end();
    }

    void push_front(const Object &x)
    {
        insert(begin(), x);
    }

    void push_back(const Object &x)
    {
        insert(end(), x);
    }

    void pop_front()
    {
        erase(begin());
    }

    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator iter, const Object &x);
    iterator erase(iterator iter);
    iterator erase(iterator start, iterator end);

private:
    void init();

    int the_size_;
    Node *head_;
    Node *tail_;
};

#endif  // DATASTRUCTURE_LIST_H_
