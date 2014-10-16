#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>

<<<<<<< HEAD
template<class E>
class Node

{
private:
    Node *left;
    Node *right;
    E content;
public:
=======
template<class E> class Node
{
public:
    E content;
>>>>>>> 836a9ade65c12ccce9f31a8e31e4a3c996620627
    Node() {
        this->left = 0;
        this->right = 0;
    }
<<<<<<< HEAD
=======
    Node *left;
    Node *right;
>>>>>>> 836a9ade65c12ccce9f31a8e31e4a3c996620627
    int height(Node * base) {
        if(base == 0) {
            return 0;
        }
        return 1 + qMax<int>(height(base->left), height(base->right));
    }
    void show(Node *base) {
        if(base == 0) {
            return;
        }
        show(base->left);
        show(base->right);
        qDebug() << "Node:" << base->content;
    }
    int childCount(Node *base) {
        if(base == 0) {
            return 1;
        }
        return childCount(base->left) + childCount(base->right);
    }

    bool isFull(Node *base)
    {
        if(base == 0)
        {
//            qDebug() << "If 1";
            return true;
        }
<<<<<<< HEAD
        else if((base->left != 0 && base->right == 0) ||
           			(base->left == 0 && base->right != 0))
=======
        if((base->left != 0 && base->right == 0) ||
           (base->left == 0 && base->right != 0))
>>>>>>> 836a9ade65c12ccce9f31a8e31e4a3c996620627
        {
//            qDebug() << "If 2";
            return false;
        }
        return isFull(base->right) * isFull(base->left);
    }
};

#endif // NODE_HPP
