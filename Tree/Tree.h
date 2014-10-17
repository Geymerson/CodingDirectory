#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"
#include "Node.h"
#include <QDebug>

template<typename E>
class Tree: public BinTree<E>
{
private:
    E m_maxValue; //max value
    E m_minValue; //min value
    E m_preMaxValue; //previos max value
    E m_preMinValue; //previous min value
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

    void clear()
    {
        m_root->clear(m_root);
        m_root = 0;
        m_current = m_root;
        m_minValue = 0;
        m_maxValue = 0;
    }

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
        else if(item < m_root->content && m_root->left == 0)
        {
            m_root->left = new Node<E>(item);
        }
        else if(item > m_root->content && m_root->right == 0)
        {
            m_root->right = new Node<E>(item);
        }
        else
        {
            while((item < temp->content) && (temp->left != 0)) //Moves left while a place to the new node isn't found
            {                                               //the node is attached to the tree as soon as a space is found
                temp = temp->left;
                qDebug() << temp->content;
                if(item < temp->content && temp->left == 0)
                {
                    temp->left = new Node<E>(item);
                }
                else if(item > temp->content && temp->right == 0)
                {
                    temp->right = new Node<E>(item);
                }
            }
            while((item > temp->content) && (temp->right != 0)) //Moves right while a place to the new node isn't found
            {                                               //the node is attached to the tree as soon as a space is found
                temp = temp->right;
                qDebug() << temp->content;
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
