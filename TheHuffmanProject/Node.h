#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>
#include <QDebug>
#include <iostream>
#include <QtCore/qmath.h>

using namespace std;

template<class E>
class Node
{
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

    void clear(Node *root) //deleta a arvore
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

    Node *getNode(Node *root, E value) //procura o node que contem o valor "item" na árvore
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

    void removeNode(Node *root, E value)
    {
        if(root != 0 && root->withinTree(root, value))
        {
            Node *temp1, *temp2, *temp3, *temp4; //variáveis temporárias
            temp1 = getNode(root, value); //procura o nó a ser removido
            temp2 = nodeAbove(root, value); //procura o nó acima daquele a ser removido

            if(temp1->left == 0 && temp1->right == 0) //se for uma folha, remover
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
            else //O nó a ser removido tem ambos os filhos
            {
                temp3 = minNode(temp1->right); //Procura o menor valor do lado direio da árvore
                if(temp3->right != 0)
                {
                    temp4 = nodeAbove(root, temp3->content); //Nó acima do menor nó do lado direito da árvore
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
