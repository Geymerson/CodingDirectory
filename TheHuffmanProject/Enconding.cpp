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
            //qDebug() << count[j] << j;
            list.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }

//################### building of the tree #########################

    Node<int> *temp, *root;
    int sum = 0;

    list.bubbleSort();

    sum = list.getQuantity();
    list.next();
    sum += list.getQuantity();

    list.moveToStart();

    temp = new Node<int>(0, sum);
    temp->left = new Node<int>(list.getValue(), list.getQuantity());
    list.remove();
    temp->right = new Node<int>(list.getValue(), list.getQuantity());
    list.remove();

    list.pInsert(temp->content, temp->quantity, temp);

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
