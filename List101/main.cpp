#include "linkedlist.h"
#include <QDebug>

int main()
{
    //########### Insertion/Append function test #########

    LinkedList<int> llist;
    llist.append(1);
    llist.insert(7);
    llist.append(2);
    llist.append(3);
    llist.insert(9);
    llist.append(4);
    llist.

    for(int i = 1; i <= llist.length(); i++)
    {
        qDebug() << "Value:"<< llist.getValue() << "Current Position" << llist.currPos();
        llist.next();
    }

    //--------------------------------------------------

    //########### Position-change functions test #########

    llist.moveToPos(3);
    qDebug() <<endl<<"Move to Position(3):" <<"Current Position"<< llist.currPos() << "value" << llist.getValue();

    llist.moveToEnd();
    qDebug() << "Move to End:" << llist.currPos()<<"Value"<<llist.getValue();

    llist.prev();
    qDebug() << "Previous position:" << llist.currPos()<<"Value"<<llist.getValue();
    llist.prev();
    qDebug() << "Previous position:" << llist.currPos()<<"Value"<<llist.getValue();
    llist.prev();
    qDebug() << "Previous position:" << llist.currPos()<<"Value"<<llist.getValue();

    llist.moveToStart();
    qDebug() << "Move to start:" << llist.currPos();

    //--------------------------------------------------

    //##################### length #####################

    qDebug() <<"List size:"<< llist.length();

    //--------------------------------------------------

    //########### Remove functions test #########

    qDebug() << "Node at position" << llist.currPos() << "with value" << llist.remove() << "has been removed.";
    qDebug() <<"Current List Size" <<llist.length();
    llist.moveToEnd();

    qDebug() << "Value:"<< llist.getValue() << "Current Position" << llist.currPos();
    qDebug() << "Value" << llist.remove() << "has been removed" << "at position" << llist.currPos();
    qDebug() << "Value" << llist.getValue() << "Current position" << llist.currPos();

    //--------------------------------------------------

    return 0;
}
