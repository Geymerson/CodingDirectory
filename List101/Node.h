#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    T content;
    Node *next;
    Node(T content) {
        this->content = content;
        this->next = 0;
    }
};

#endif // NODE_H
