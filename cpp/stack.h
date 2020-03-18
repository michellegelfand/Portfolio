#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

struct Stack
{
    public:
    void Push(int value);
    void Pop();
    int Top() const;
    bool IsEmpty() const;
    size_t Size() const;
    explicit Stack();

    private:

    struct Node
    {  
        private:
        const int value;
        const Node *prev;

        public:
        bool HasPrev() const;
        const Node *GetPrev() const;
        int GetData() const;

        explicit Node(int value, Node *head);

    };

    Node *head;

};

#endif /* __STACK_H__ */

