#include "LQueue.h"
#include <QDebug>

int main()
{
    LQueue<int> list;

    //list.dequeue();

    list.enqueue(3);
    list.enqueue(2);
    list.enqueue(3);
    list.enqueue(6);
    list.enqueue(7);
    list.enqueue(8);

    qDebug() << list.frontValue();
    qDebug() << list.length();
    qDebug() << list.dequeue();
    qDebug() << list.length();
    qDebug() << list.frontValue();

    //list.clear();

    //list.dequeue();

    return 0;
}
