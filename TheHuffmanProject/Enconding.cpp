#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "Encoding.h"
#include "LinkedList.h"
#include "Tree.h"


int encoding(QString fileName)
{
    int count[256] = {0};
    QFile file(fileName);
    LinkedList<int> list;

    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "The file could not be read";
        return 1;
    }
//############# Character count and making the the linked list #############

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

//################### building of the tree #########################
//Do not to forget to delete the tree to clear the memory
    Node<int> *tree;
    int sum;

    qDebug() << "Before the Loop";

    while(list.length() != 1)
    {
        //qDebug() << "In the Loop";
        list.bubbleSort();//Ordenate the list
       //qDebug() << "In the Loop";

        sum = list.getQuantity();
        list.next();
        sum += list.getQuantity(); //Get the sum of two nodes

       //qDebug() << "sum:" << sum;

        list.moveToStart(); //moves to the start of the list

        tree = new Node<int>(0, sum); //creating a node

        //qDebug() << "In the Loop";

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


    //tree->clear(tree);
    //qDebug() << tree->leafCount(tree);

//##############################################################

//    QFile treeFile("tree.huffman");
//    treeFile.open(QIODevice::WriteOnly);
//    QTextStream out(&treeFile);
//    out << "Sample: " << 49 << "\n";
//    treeFile.close();
    //tree->show(tree);



    return 0;
}

QByteArray toString(Node<int> *tree, QByteArray k)
{
    if(!tree->isLeaf(tree))
    {
        k.append('!');
    }

    toString(tree->left, k);
    toString(tree->right, k);

    k.append(40);
    return k;
}
