#ifndef NODE_HPP
#define NODE_HPP

#include <QObject>
#include <QDebug>
#include <QtCore/qmath.h>
#include <iostream>

using namespace std;

template<class E>
class Node
{
private:
   E m_treeVector[10][10]; //vetor usado para toString
public:
    E content;
    Node *left;
    Node *right;
    Node()
    {
        this->left = 0;
        this->right = 0;
        for(int i = 0; i < 10; i++)
        {
            m_treeVector[i][0] = false;
        }
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

    void clear(Node *root) //deleta a arvore
    {
        if(root == 0)
        {
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }

    bool withinTree(Node *node, E value) //verifica se "value" pertence a árvore
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

    Node *maxNode(Node * root) //procura o maior valor da árvore
    {
        if(root != 0)
        {
            while(root->right != 0)
            {
                root = root->right;
            }
        }
        return root;
    }

    Node *minNode(Node *root) //Procura o menor valor da árvore
    {
        if(root != 0)
        {
            while(root->left != 0)
            {
                root = root->left;
            }
        }
        return root;
    }

    Node *nodeAbove(Node *root, E value) //Retorna o pai de um nó
    {
        if(root != 0 && (withinTree(root, value)) && (root->content != value)) //A funçao apenas executa se value
        {                                                                      //pertencer a árvore e não é a raiz
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

    void removeNode(Node *root, E value) //Remove um nó
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

    void scanTree(Node *base, int height) //Faz uma pesquisa na árvore a fim de definir qual nó pertence a
        {                                   //qual nível de profundidade
            if(base == 0)
            {
                return;
            }

            int level = height - 1;

            if(level > 0) //bloco de comando que cuida dos ramos vazios
            {
                int n = 0;

                if(base->left == 0)
                {
                    while(m_treeVector[level - 1][n++] != false) { }
                    m_treeVector[level - 1][n] = true;
                    n = 0;
                }
                if(base->right == 0)
                {
                    while(m_treeVector[level - 1][n++] != false) {}
                    m_treeVector[level - 1][n] = true;
                }
            }

            int i = 0;
            while(m_treeVector[level][i] != false) //O vetor e percorrido até uma posicao vaga ser encontrada
            {
                i++;
            }

            m_treeVector[level][i] = base->content;
            m_treeVector[level][++i] = false;

            scanTree(base->left, height - 1);
            scanTree(base->right, height - 1);
        }

        void printTree(Node *base) //Printa a árvore binária
        {
            scanTree(base, base->height(base));

            int level = base->height(base) - 1;

            for(int i = level; i >= 0; i--)
            {
                for(int k = 0; m_treeVector[i][k] != false; k++)
                {
                    if(k == 0)
                    {
                        for(int j = 0; j < qPow(2, i) - 1; j++)
                        {
                            cout << ' ';
                        }
                        cout << m_treeVector[i][k];
                    }
                    else
                    {
                        for(int j = 0; j < (2 * qPow(2, i)) - 1; j++)
                        {
                            cout << ' ';
                        }
                        cout << m_treeVector[i][k];
                    }
                }
                cout << endl;
            }
        }
};

#endif // NODE_HPP
