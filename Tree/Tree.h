#ifndef TREE_H
#define TREE_H

#include "TreeADT.h"
#include "Node.h"

template<typename E>
class Tree: public BinTree<E>
{
private:
    E m_maxValue; //max value
    E m_minValue; //min value
    E m_preMaxValue; //previos max value
    E m_preMinValue; //previous min value
    int m_treeSize;
    int m_leafQuantity;
    int m_nodeQuantity;
    int m_levelQuantity;
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

    void clear()
    {
        clearTraversal(m_root);
        m_root = 0;
        m_current = m_root;
        m_minValue = 0;
        m_maxValue = 0;
        m_nodeQuantity = 0;
        m_leafQuantity = 0;
        m_levelQuantity = 0;
        m_treeSize = 0;
    }

    void clearTraversal(Node<E> *root)
    {
        Node<E> * temp = root;
        if(root == 0)
        {
            return;
        }
        clearTraversal(root->left);
        clearTraversal(root->right);
        qDebug() << "Deleting " << temp->content;
        delete temp;
    }

    void add(const E& item)
    {
        Node<E> *temp;

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
            temp = m_root;
        }
        else
        {
            temp = m_root;
            while((item < temp->content) && (temp->left != 0)) //Moves left while a place to the new node isn't found
            {                                               //the node is attached to the tree as soon as a space is found
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
            while((item > temp->content) && (temp->right != 0)) //Moves right while a place to the new node isn't found
            {                                               //the node is attached to the tree as soon as a space is found
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

    E getHere() const
    {
        return m_current->content;
    }
};

#endif // TREE_H
