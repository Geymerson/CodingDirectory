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

    int height(Node * base)
    {
        if(base == 0) {
            return 0;
        }
        return 1 + qMax<int>(height(base->left), height(base->right));
    }

    void show(Node *base)
    {
        if(base == 0) {
            return;
        }
        show(base->left);
        show(base->right);
        qDebug() << "Node:" << base->content;
    }

    int childCount(Node *base)
    {
        if(base == 0) {
            return 1;
        }
        return childCount(base->left) + childCount(base->right);
    }

    int leafCount(Node *base)
    {
        if(base == 0) {
            return 0;
        }
        if(base->left == 0 && base->right == 0)
        {
            return 1;
        }
        return leafCount(base->left) + leafCount(base->right);
    }

    void clear(Node *root)
    {
        if(root == 0)
        {
            return;
        }
        clear(root->left);
        clear(root->right);
        qDebug() << "Deleting " << root->content;
        delete root;
    }

    bool withinTree(Node *node, E value)
    {
        if(node == 0)
        {
            return 0;
        }
        if(node->content == value)
        {
            return 1;
        }
        return  withinTree(node->left, value) + withinTree(node->right, value);
    }
};

#endif // NODE_HPP
