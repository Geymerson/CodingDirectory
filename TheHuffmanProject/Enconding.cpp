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
//############# Contagem de caracteres e criação da lista ligada #############

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
            qDebug() << count[j] << j;
            list.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }

//################### building of the tree #########################

    Node<int> *tree;
    int sum;

    qDebug() << "Before the Loop";

    while(list.length() != 1)
    {
        //qDebug() << "In the Loop";
        list.bubbleSort();
       //qDebug() << "In the Loop";

        sum = list.getQuantity();
        list.next();
        sum += list.getQuantity();

       //qDebug() << "sum:" << sum;

        list.moveToStart();

        tree = new Node<int>(0, sum);

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



//    for(int i = 0; i < temp.length(); i++)
//    {
//        temp.getValue();
//        temp.next();
//    }
//    temp.moveToStart();
//    temp.bubbleSort();
//    qDebug() << endl;
//    for(int i = 0; i < temp.length(); i++)
//    {
//        temp.getValue();
//        temp.next();
//    }
    return 0;
}
