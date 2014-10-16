#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"
#include "Node.h"

template<typename E>
class Tree: public BinTree<E>
{
private:
    E m_maxValue;
    E m_preMaxValue;
    E m_minValue;
    E m_preMinValue;
    int m_treeSize;
    int m_leafQuantity;
    int m_nodeQuantity;
    int m_currentLevel;
    Node<E> *m_root;
    Node<E> *m_current;
public:
    Tree()
    {
        m_root = 0;
        m_minValue = 0;
        m_maxValue = 0;
        m_nodeQuantity = 0;
        m_current = m_root;
    }
    ~Tree(){}

    void add(const E& item)
    {
        Node<E> *temp = m_root;

        if(item > m_maxValue)
        {
            m_preMaxValue = m_maxValue;
            m_maxValue = item;
        }
        if(item < m_minValue)
        {
            m_preMinValue = m_minValue;
            m_minValue = item;
        }

        if(m_root == 0)
        {
            m_root = new Node<E>(item);
        }
        else
        {
            while(item < temp->content && temp->left != 0)
            {
                temp = temp->left;
                if(item < temp->content && temp->left == 0)
                {
                    temp->left = new Node<E>(item);
                }
                else if(item > temp->content && temp->right == 0)
                {
                    temp->right = new Node<E>(item);
                }
            }
            while(item > temp->content && temp->right != 0)
            {
                temp = temp->right;
                if(item < temp->content && temp->left == 0)
                {
                    temp->left = new Node<E>(item);
                }
                else if(item > temp->content && temp->right == 0)
                {
                    temp->right = new Node<E>(item);
                }
            }
        }
        m_nodeQuantity++;
    }

    const E lower()
    {
        return m_minValue;
    }

    const E greater()
    {
        return m_maxValue;
    }

    int countNode() const
    {
        return m_nodeQuantity;
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
};

#endif // TREE_H
