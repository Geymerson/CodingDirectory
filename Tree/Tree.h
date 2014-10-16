#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"

template<typename Key, typename E>
class Tree: public BinTree<E>
{
private:
    E m_maxValue;
    E m_preMaxValue;
    E m_minValue;
    E m_preMinValue;
    Node<E> *m_root;
    Node<E> *m_current;
public:
    Tree()
    {
        m_root = 0;
        m_minValue = 0;
        m_maxValue = 0;
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
    }
};

#endif // TREE_H
