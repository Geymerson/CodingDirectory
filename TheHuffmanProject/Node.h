#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>
#include <QDebug>

template<class E>
class Node
{
private:
public:
    int quantity;
    E content;
    Node *next;
    Node *left;
    Node *right;

    Node()
    {
        this->next = 0;
        this->left = 0;
        this->right = 0;
    }

    Node(const E& value, const int& count)
    {
        this->content = value;
        this->quantity = count;
        this->next = 0;
        this->left = 0;
        this->right = 0;
    }

    Node(const E& value, const int& count, Node *ptr)
    {
        this->content = value;
        this->quantity = count;
        this->right = ptr;
        this->next = 0;
        this->left = 0;
    }

    //gets the height of the tree
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
        if(base == 0)
        {
            return;
        }
        qDebug() << base->content;
        base->show(base->left);
        base->show(base->right);
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

    //Searchs for the node that contains "value" in the tree
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

    //removes the node that contains "value" in the tree
    void removeNode(Node *root, E value)
    {
        if(root != 0 && root->withinTree(root, value))
        {
            Node *temp1, *temp2, *temp3, *temp4; //temporary variables
            temp1 = getNode(root, value); //searchs for the node being removed
            temp2 = nodeAbove(root, value); //searchs for the node above the one being removed

            if(temp1->left == 0 && temp1->right == 0) //if it's a leaf, remove it.
            {
                if(temp2->right->content == value)
                {
                    temp2->right = 0;
                }
                else
                {
                    temp2->left = 0;
                }
                delete temp1;
            }
            else if(temp1->left != 0 && temp1->right == 0)
            {
                temp2->right = temp1->left;
                delete temp1;
            }
            else if(temp1->left == 0 && temp1->right != 0)
            {
                temp2->right = temp1->right;
                delete temp1;
            }
            else //The node being removed has it's both children
            {
                temp3 = minNode(temp1->right); //Searchs the minor node at the right side of the tree
                if(temp3->right != 0)
                {
                    temp4 = nodeAbove(root, temp3->content); //Node above the minor node at the right side of the tree
                    if(temp4->left->content == temp3->content)
                    {
                        temp4->right = temp3->right;
                    }
                    else
                    {
                        temp4->left = temp3->right;
                    }
                }
                delete temp3;
            }
        }
    }
};

#endif // NODE_HPP
