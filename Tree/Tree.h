#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"
#include "Node.h"
#include <QDebug>

template<typename E>
class Tree: public BinTree<E>
{
private:
    Node<E> *m_root;
    Node<E> *m_current;
public:
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

    void remove(E item)
    {
        m_root->removeNode(m_root, item);
    }


    void add(const E& item)
    {
        Node<E> *temp = m_root;

        if(m_root == 0)
        {
            m_root = new Node<E>(item);
        }
        else
        {
            while(true)
            {
                if(item < temp->content && temp->left == 0)
                {
                    temp->left = new Node<E>(item);
                    break;
                }
                else if(item < temp->content && temp->left != 0)
                {
                    temp = temp->left;
                }
                else if(item > temp->content && temp->right == 0)
                {
                    temp->right = new Node<E>(item);
                    break;
                }
                else if(item > temp->content && temp->right != 0)
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

    int countNode() const
    {
        return m_root->childCount(m_root);
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

    Node<E> getTree() const
    {
        return *m_root;
    }

    E getHere() const
    {
        return m_current->content;
    }

    int height() const
    {
        return m_root->height(m_root);
    }

    int countLevel() const
    {
        if(m_root != 0)
        {
            return m_root->height(m_root) - 1;
        }
        return 0;
    }

    int countLeaf() const
    {
        return m_root->leafCount(m_root);
    }

    bool inTree(E item)
    {
        return m_root->withinTree(m_root, item);
    }

};

#endif // TREE_H
