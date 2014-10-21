#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>
#include <QDebug>

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
        if(base == 0)
        {
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
            return true;
        }
        return  withinTree(node->left, value) + withinTree(node->right, value);
    }

    Node *getNode(Node *root, E value)
    {
        if(root != 0)
        {
            while(root->content != value && root != 0)
            {
                if(value < root->content)
                {
                    root = root->left;
                }
                else if(value > root->content)
                {
                    root = root->right;
                }
            }
      }
      return root;
    }

    Node *maxNode(Node * root)
    {
        if(root != 0)
        {
            while(root->right != 0)
            {
                root = root->right;
            }
            return root;
        }
    }

    Node *minNode(Node *root)
    {
        if(root != 0)
        {
            while(root->left != 0)
            {
                root = root->left;
            }
            return root;
        }
    }

    Node *nodeAbove(Node *root, E value)
    {
        if(root != 0 &&
            (withinTree(root, value)) &&
                (root->content != value))
        {
            while(true)
            {
                if(value > root->content && root->right != 0)
                {
                    if(root->right->content == value)
                    {
                        return root;
                    }
                    else
                    {
                        root = root->right;
                    }
                }
                else if(value < root->content && root->left != 0)
                {
                    if(root->left->content == value)
                    {
                        return root;
                    }
                    else
                    {
                        root = root->left;
                    }
                }
            }
        }
    }

    void removeNode(Node *root, E value)
    {

    }
};

#endif // NODE_HPP
