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
    LinkedList<int> list, list2; //list to creat the tree, list2 to chararcter's codification

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
        for(int i = 0; i < line.size() - 1; ++i)
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
    Node<int> *tree;
    int sum;
    //qDebug() << "Before the Loop";
    list.bubbleSort();
    list2 = list;
    while(list.length() != 1)
    {
        sum = list.getQuantity();
        list.next();
        sum += list.getQuantity(); //Get the sum of two nodes
        list.moveToStart(); //moves to the start of the list
        tree = new Node<int>(0, sum); //creating a node
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
        list.bubbleSort();//Ordenate the list
    }


    //tree->clear(tree);
    //qDebug() << tree->leafCount(tree);
    //    QFile treeFile("tree.huffman");
    //    treeFile.open(QIODevice::WriteOnly);
    //    QTextStream out(&treeFile);
    //    out << "Sample: " << 49 << "\n";
    //    treeFile.close();
    //    qDebug() << tree->leafCount(tree);
    //   tree->show(tree);
    //    for(int i = 0; i < k.size(); i++)
    //    {
    //        qDebug() << k[i];
    //    }

//############################ Tree representation ##################################

    QByteArray k;
    toString(tree, &k);
    qDebug() << k;

//############################ Generatin the Codification ##########################

    QString p;
    charCodification(tree, 0, 0, &p);
    return 0;
}

//Creats the codification of the characters
void charCodification(Node<int> *tree, Node<int> *left, Node<int> *right, QString *codification)
{
    if(tree != 0)
    {
        Node<int> *temp = tree;

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
           codification->remove(codification->size() - 1, 1);
           return;
        }
        charCodification(tree->left, tree->left, tree->right, codification);
        charCodification(tree->right, tree->left, tree->right, codification);
        codification->remove(codification->size() - 1, 1);
        return;
    }
}

//Creates the representation of the tree
void toString(Node<int> *tree, QByteArray *k)
{
    if(tree->isLeaf(tree))
    {
        if(tree->content == 40)
        {
            k->append(42).append(tree->content);
        }
        else
        {
            k->append(tree->content);
        }
        return;
    }
    k->append(40);
    toString(tree->left, k);
    toString(tree->right, k);
    return;
}
