#include <QFile>
#include <QByteArray>
#include <QDebug>
#include "Encoding.h"
#include "LinkedList.h"

int encoding(QString fileName)
{
    int count[256] = {0};
    QFile file(fileName);
    LinkedList<int> temp;

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
            temp.insert(j, count[j]); //inserting character, character quantity in a linked list
        }
    }


//############# Ordenação da lista #############


    return 0;
}
