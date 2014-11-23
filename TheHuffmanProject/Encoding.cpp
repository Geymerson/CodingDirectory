#include <QFile>
#include <QByteArray>
#include <QBitArray>
#include <QDebug>
#include "Encoding.h"
#include "LinkedList.h"

int encoding(QString fileName)
{
    int count[256] = {0};
    QFile file(fileName);
    LinkedList<int, int> list; //list to creat the tree

//############################## Openning the File ##################################

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//################## Character count and making the the linked list #################

    while (!file.atEnd())
    {
        QByteArray line = file.readLine(1024);
        for(int i = 0; i < line.size(); ++i)
        {
            ++count[(unsigned char) line.at(i)];
        }
    }
    for(int j = 0; j < 256; ++j) // "j"represents the character
    {
        if(count[j])
        {
            //qDebug() << count[j] << j;
            //QString ch = QString::number(j,16);
            //qDebug() << ch;
            list.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }

//    for(int i = 0; i < list.length(); i++)
//    {
//        qDebug() << list.getValue();
//        list.next();
//    }

//############################### building the tree ##############################

//Do not to forget to delete the tree to clear the memory
    Node<int, int> *tree;
    int sum;
    while(list.length() != 1)
    {
        list.bubbleSort();//Ordenate the list
        sum = list.getQuantity();
        list.next();
        sum += list.getQuantity(); //Holds the sum of the two first nodes quantity
        list.moveToStart(); //moves to the start of the list
        tree = new Node<int, int>(0, sum);
        if(list.getPointer())
        {
            tree->left = list.getPointer();
        }
        else
        {
            tree->left = new Node<int, int>(list.getValue(), list.getQuantity());
        }
        list.remove();
        if(list.getPointer())
        {
            tree->right = list.getPointer();
        }
        else
        {
            tree->right = new Node<int, int>(list.getValue(), list.getQuantity());
        }
        list.remove();
        list.pInsert(tree->content, tree->quantity, tree);
    }

//############################ Tree representation ##################################

    QByteArray treeRep;
    treeRepresentation(tree, &treeRep); //treeRep holds the representation of the tree
    //qDebug() << treeRep;

//############################ Generating the Codification ##########################

    QString aux;
    LinkedList<int, QString> codList; //value holds the char, quantity holds the codification
    charCodification(tree, 0, 0, &aux, &codList); //aux becomes a list holding a char and it's codification

//    qDebug() << codList.length();
//    codList.moveToEnd();
//    for(int i = 0; i < codList.length(); i++)
//    {
//        qDebug() << codList.getValue() << codList.getQuantity() << codList.currPos();
//        codList.prev();
//    }

//    codList.moveToStart();
//    for(int i = 0; i < codList.length(); i++)
//    {
//        qDebug() << codList.getValue() << codList.getQuantity() << codList.currPos();
//        codList.next();
//    }

    QFile codFile("codFile.huff");
    codFile.open(QIODevice::WriteOnly);
    QTextStream out(&codFile);
    file.seek(0); //Move the cursor to the start of the file

    while (!file.atEnd())
    {
        QByteArray line = file.readLine(1024);
        for(int i = 0; i < line.size(); ++i)
        {
            unsigned char ch = (unsigned char) line.at(i);
            if(codList.seekValue(ch))
            {
                out << codList.getQuantity();
                codList.swap();
            }
        }
    }

//    codList.moveToStart();
//    for(int i = 0; i < codList.length(); i++)
//    {
//        qDebug() << codList.getValue() << codList.getQuantity() << codList.currPos();
//        codList.next();
//    }

    //codFile.close();
    //codFile.remove();

//    out << "Sample: " << 49 << "\n";
//    treeFile.close();
//    qDebug() << tree->leafCount(tree);
//    tree->show(tree);
//    for(int i = 0; i < k.size(); i++)
//    {
//        qDebug() << k[i];
//    }
    return 0;
}

//Creats the codification of the characters
void charCodification(Node<int, int> *tree, Node<int, int> *left, Node<int, int> *right,
                      QString *codification, LinkedList<int, QString> *list)
{
    if(tree != 0)
    {
        Node<int, int> *temp = tree;

        if(temp == left)
        {
            codification->append(QString::number(1, 10));
        }
        else if(temp == right)
        {
            codification->append(QString::number(0, 10));
        }
        if(tree->isLeaf(tree))
        {
           //qDebug() << tree->content << ":"<< *codification;
           list->insert(tree->content, *codification);
           codification->remove(codification->size() - 1, 1);
           return;
        }
        charCodification(tree->left, tree->left, tree->right, codification, list);
        charCodification(tree->right, tree->left, tree->right, codification, list);
        codification->remove(codification->size() - 1, 1);
        return;
    }
}

//Creates the representation of the tree
void treeRepresentation(Node<int, int> *tree, QByteArray *k)
{
    if(tree->isLeaf(tree))
    {
        if(tree->content == 40)
        {
            k->append(QString::number(42, 16)).append(QString::number(tree->content, 16));
        }
        else
        {
            k->append(QString::number(tree->content, 16));
        }
        return;
    }
    k->append(40);
    treeRepresentation(tree->left, k);
    treeRepresentation(tree->right, k);
    return;
}
