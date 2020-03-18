
#include "stack.h"



Stack::Node::Node(int value, Node *head)
    :value(value), prev(head)
{
    ;
}

Stack::Stack()
    :head(NULL)
{
    ;
}


int Stack::Top() const
{
   return head->GetData(); 
}

bool Stack::IsEmpty() const
{
    return (head ? false: true);
}

size_t Stack::Size() const
{
    size_t count = 0;
    const Node *traverser = head;
    while(traverser)
    {
        traverser = traverser->GetPrev();
        ++count;
    }

    return count;
}

void Stack::Push(int value)
{
    Node *new_top = new Node(value, head);
    head = new_top; 
}

void Stack::Pop()
{
    Node *prev = (Node*)head->GetPrev();
    head = (Node*)prev; 
}

int Stack::Node::GetData() const
{
    return value;
}

bool Stack::Node::HasPrev() const
{
   return ( GetPrev() ? true : false);
}

const Stack::Node *Stack::Node::GetPrev() const
{
    return prev;
}