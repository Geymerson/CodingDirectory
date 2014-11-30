#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "Encoding.h"
#include "LinkedList.h"

//Creates the codification of the characters
bool charCodification(Node<int> *tree, Node<int> *left,
                      Node<int> *right, QString aux[], QString sample)
{
    if(tree != 0)
    {
        Node<int> *temp = tree;

        if(temp == left)
        {
            sample.append(QString::number(0, 10));
        }
        else if(temp == right)
        {
            sample.append(QString::number(1, 10));
        }
        if(tree->isLeaf(tree))
        {
           aux[tree->content] = sample;
           //qDebug() << tree->content << ":"<< aux[tree->content];
           sample.remove(sample.size() - 1, 1);
           return true;
        }
        charCodification(tree->left, tree->left, tree->right, aux, sample);
        charCodification(tree->right, tree->left, tree->right, aux, sample);
        sample.remove(sample.size() - 1, 1);
        return true;
    }
    return false;
}

//Creates the representation of the tree
void treeRepresentation(Node<int> *tree, QByteArray *k)
{
    if(tree->isLeaf(tree))
    {
        if(tree->content == 40)
        {
            k->append('*').append((unsigned char)tree->content);
        }
        else
        {
            k->append((unsigned char)tree->content);
        }
        return;
    }
    k->append('(');
    treeRepresentation(tree->left, k);
    treeRepresentation(tree->right, k);
    return;
}

//Creates the file codification
int encoding(QString fileName)
{
    QString aux1;
    QByteArray aux2, aux3;
    LinkedList<int> list; //list to create the tree
    int count[256] = {0};

    QFile file(fileName);

    QFile codFile("codFile.huff");
    codFile.open(QIODevice::WriteOnly);

    aux2.append("00"); //First two bytes for trash and tree size
    aux2.append(fileName.length());
    aux2.append(fileName);
    codFile.write(aux2);
    aux2.clear();

//############################## Openning the File ##################################

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//################## Character count and making the the linked list #################

    while (!file.atEnd())
    {
        QByteArray line = file.read(8000);
        for(int i = 0; i < line.size(); ++i)
        {
            ++count[(unsigned char) line.at(i)];
        }
    }
    for(int j = 0; j < 256; ++j) // "j"represents the character
    {
        if(count[j])
        {
            list.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }

//############################### building the tree ##############################

    Node<int> *tree;
    int sum;

    if(list.length() == 1)
    {
        tree = new Node<int>(list.getValue(), list.getQuantity());
    }
    else
    {
        while(list.length() != 1)
        {
            list.bubbleSort();//Ordenate the list
            sum = list.getQuantity();
            list.next();
            sum += list.getQuantity(); //Holds the sum of the two first nodes quantity
            list.moveToStart(); //moves to the start of the list
            tree = new Node<int>(0, sum);
            if(list.getPointer())
            {
                tree->left = list.getPointer();
            }
            else
            {
                tree->left = new Node<int>(list.getValue(), list.getQuantity());
            }
            list.remove();
            if(list.getPointer())
            {
                tree->right = list.getPointer();
            }
            else
            {
                tree->right = new Node<int>(list.getValue(), list.getQuantity());
            }
            list.remove();
            list.pInsert(tree->content, tree->quantity, tree);
        }
    }

//############################ Tree representation ##################################

    QByteArray treeRep;
    treeRepresentation(tree, &treeRep); //treeRep holds the representation of the tree
    codFile.write(treeRep);
//    qDebug() << treeRep;
//    qDebug() << treeRep.length();

//############################ Generating the Codification ##########################

    QString codVector[256];
    if(tree->isLeaf(tree))
    {
        QString temp('0');
        codVector[(unsigned char)tree->content] = temp;
    }
    else
    {
        charCodification(tree, 0, 0, codVector, aux1);//Now CodVector has char's codification
    }
    int trash = 0;

    QByteArray codArray;
    bool ok;
    file.seek(0); //Move the cursor to the start of the

    while (!file.atEnd())
    {
        QByteArray line = file.read(8000);
        for(int i = 0; i < line.size(); ++i)
        {
            codArray.append(codVector[(unsigned char) line.at(i)]);
            if(!(codArray.length() % 8))
            {
                char ch = (unsigned char) codArray.toInt(&ok,2);
                aux2.append(ch);
                codArray.clear();
                if(aux2.length() >= 1000)
                {
                    codFile.write(aux2);
                    aux2.clear();
                }
            }
        }
        if(file.atEnd())
        {
            if(codArray.length() % 8)
            {
                trash = 8 - (codArray.length() % 8);

                for(int i = 0; i < trash; i++)
                {
                    codArray.append('0');
                }
                char ch = (unsigned char)codArray.toInt(&ok, 2);
                aux2.append(ch);
                codArray.clear();
            }
        }
    }
    codFile.write(aux2);
    aux2.clear();

//############################ Formating trash and treeSize #########################

    QByteArray bTrash, treeSize;
    bTrash.append(QByteArray::number(trash, 2));
    treeSize.append(QByteArray::number(treeRep.length(), 2));

    while((aux2.length() + bTrash.length()) != 3)
    {
        aux2.append('0');
    }
    aux2.append(bTrash);

    while((aux3.length() + treeSize.length()) != 13)
    {
        aux3.append('0');
    }
    aux3.append(treeSize);
    aux2.append(aux3);
    aux3.clear();

    codFile.seek(0);
    for(int i = 0; i < 16; i++)
    {
        aux3.append(aux2.at(i));
        if(aux3.length() == 8)
        {
            char ch = (unsigned char)aux3.toInt(&ok, 2);
            codArray.append(ch);
            codFile.write(codArray);
            aux3.clear();
            codArray.clear();
        }
    }

    codFile.close();
    file.close();
    tree->clear(tree);
    return 0;
}
