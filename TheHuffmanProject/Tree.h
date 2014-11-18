#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"
#include "Node.h"
#include <QDebug>


template<typename E>
class Tree: public BinTree<E>
{
private:
public:
    Node<E> *m_root;
    Node<E> *m_current;
    Tree()
    {
        m_root = 0;
        m_current = m_root;
    }

    ~Tree()
    {
        clear();
    }

    void clear()
    {
        m_root->clear(m_root);
        m_root = 0;
        m_current = m_root;
    }

    void addSubTree(Node<E> *node)
    {
        if(m_root != 0 && (node->content != m_root->content))
        {
            Node<E> *temp1 = m_root;
            Node<E> *temp2 = node;

            qDebug() << "asdas" << temp2->content;

            while(true)
            {
                if(temp2->content < temp1->content && temp1->left == 0)
                {
                    temp1->left = temp2;
                    break;
                }
                else if(temp2->content < temp1->content && temp1->left != 0)
                {
                    temp1 = temp1->left;
                }
                else if(temp2->content > temp1->content && temp1->right == 0)
                {
                    temp1->right = temp2;
                    break;
                }
                else if(temp2->content > temp1->content && temp1->right != 0)
                {
                    temp1 = temp1->right;
                }
            }
        }
    }

    void add(const E& item, const int& quantity)
    {
        Node<E> *temp = m_root;

        if(m_root == 0)
        {
            m_root = new Node<E>(item, quantity);
            m_current = m_root;
        }
        else
        {
            while(true)
            {
                if(item < temp->quantity && temp->left == 0)
                {
                    temp->left = new Node<E>(item, quantity);
                    break;
                }
                else if(item < temp->quantity && temp->left != 0)
                {
                    temp = temp->left;
                }
                else if(item > temp->quantity && temp->right == 0)
                {
                    temp->right = new Node<E>(item, quantity);
                    break;
                }
                else if(item > temp->quantity && temp->right != 0)
                {
                    temp = temp->right;
                }
            }
        }
    }

    const E lower()
    {
        Node<E> *temp = m_root->minNode(m_root);
        return temp->content;
    }

    const E greater()
    {
        Node<E> *temp = m_root->maxNode(m_root);
        return temp->content;
    }

    void toLeft()
    {
        if(m_current->left != 0)
        {
            m_current = m_current->left;
        }
    }

    void toRight()
    {
        if(m_current->right != 0)
        {
            m_current = m_current->right;
        }
    }

    Node<E> *getTree() const
    {
        return m_root;
    }

    E getNode() const
    {
        if(m_root != 0)
        {
            return m_current->content;
        }
    }

    int height() const
    {
        if(m_root != 0)
        {
            return m_root->height(m_root);
        }
        return 0;
    }

    int countLeaf() const
    {
        if(m_root != 0)
        {
            return m_root->leafCount(m_root);
        }
        return 0;
    }
};

#endif // TREE_H
