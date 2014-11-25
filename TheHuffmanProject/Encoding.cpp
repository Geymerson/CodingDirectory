#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "Encoding.h"
#include "LinkedList.h"

//Creates the codification of the characters
void charCodification(Node<int, int> *tree, Node<int, int> *left,
                      Node<int, int> *right, QString *codification,
                      LinkedList<int, QString> *list)
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
    k->append(QString::number(40, 16));
    treeRepresentation(tree->left, k);
    treeRepresentation(tree->right, k);
    return;
}

//Creates the file codification
int encoding(QString fileName)
{
    int count[256] = {0};
    QFile file(fileName);
    LinkedList<int, int> list; //list to create the tree

//############################## Openning the File ##################################

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }

//################## Character count and making the the linked list #################

    while (!file.atEnd())
    {
        QByteArray line = file.readLine(4049);
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

    QFile codFile("codFile.huff");
    codFile.open(QIODevice::WriteOnly);
    QTextStream in1(&codFile);
    file.seek(0); //Move the cursor to the start of the file
    long int codFileSize = 0;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine(4049);
        for(int i = 0; i < line.size(); ++i)
        {
            unsigned char ch = (unsigned char) line.at(i);
            if(codList.seekValue(ch))
            {
                in1 << codList.getQuantity();
                QString s = codList.getQuantity();
                codFileSize += s.size();
                codList.swap();
            }
        }
    }

    int trash = 8 - (codFileSize % 8);
    //qDebug() << codFileSize << trash << codFileSize % 8;
    //qDebug() << QString::number(trash, 2);

    for(int i = 0; i < trash; i++)
    {
        in1 << "0";
    }
    codFile.close();
    codFile.open(QIODevice::ReadOnly);

    QFile codFileHex("codFileHex.huff");
    codFileHex.open(QIODevice::WriteOnly);
    QTextStream in2(&codFileHex);

    QByteArray hexCodification;
    bool ok;
    long int k = trash + codFileSize;
    for(long int i = 0; i != k; i += 8)
    {
        QByteArray line = codFile.readLine(9);
        hexCodification.append(QString::number(line.toInt(&ok, 2), 16));
        //in2 << QString::number(line.toInt(&ok, 2), 16);
        //qDebug() << line;
        //qDebug() << QString::number(line.toInt(&ok, 2), 16);
    }

    qDebug() << hexCodification.length();
    in2 << hexCodification;

    codFileHex.close();
    codFile.close();
    codFile.remove();
    file.close();
    tree->clear(tree);
    return 0;
}
