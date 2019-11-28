#include <iostream>

template <typename T>
class Stack
{
  private:
    struct Node
    {
        T value;
        Node *prev;
    };
    Node *current;
    unsigned int sz;
    void Remove()
    {
        Node *temp = current->prev;
        delete current;
        current = temp;
        sz--;
    }

  public:
    Stack() : current(0), sz(0) {}
    ~Stack()
    {
        while (current)
            Remove();
    }
    void push(const T &t)
    {
        Node *temp = current;
        current = new Node();
        current->value = t;
        current->prev = temp;
        sz++;
    }
    void pop()
    {
        if (sz)
            Remove();
    }
    void print()
    {
        if (sz > 0)
        {
            Node *temp = current;
            while (temp)
            {
                std::cout << temp->value;
                temp = temp->prev;
            }
        }
        else
        {
            std::cout << "empty";
        }
    }
    T &top()
    {
        return current->value;
    }
    const T &top() const
    {
        return top();
    }
    bool empty()
    {
        return !sz;
    }
    const unsigned int &size() const
    {
        return sz;
    }
};