#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>

template<class E>
class Node
{
public:
    E content;
    Node *left;
    Node *right;
    Node()
    {
        this->left = 0;
        this->right = 0;
    }
    Node(const E& value)
    {
        this->content = value;
        this->left = 0;
        this->right = 0;
    }
};

#endif // NODE_HPP
