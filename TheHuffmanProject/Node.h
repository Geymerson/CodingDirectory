#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>
#include <QDebug>

template<class E, class T>
class Node
{
public:
    E content;
    T quantity;
    Node *next;
    Node *left;
    Node *right;

    Node()
    {
        this->next = 0;
        this->left = 0;
        this->right = 0;
    }

    Node(const E& value, const T& count)
    {
        this->content = value;
        this->quantity = count;
        this->next = 0;
        this->left = 0;
        this->right = 0;
    }

    Node(const E& value, const T& count, Node *ptr)
    {
        this->content = value;
        this->quantity = count;
        this->right = ptr;
        this->next = 0;
        this->left = 0;
    }

    //checks if the node is a leaf
    bool isLeaf(Node *base)
    {
        if(base->left == 0 && base->right == 0)
        {
            return true;
        }
        return false;
    }

    //clears the tree
    void clear(Node *root)
    {
        if(root == 0)
        {
            return;
        }
        clear(root->left);
        clear(root->right);
        //qDebug() << "Deleting " << root->content;
        delete root;
    }
};

#endif // NODE_HPP
