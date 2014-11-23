#include <QDebug>
#include "Tree.h"
#include "Node.h"

//A função toString ainda não funciona corretamente

int main()
{
    Tree<int> A;

    A.add(8);
    A.add(6);
    A.add(5);
    A.add(7);
    A.add(13);
    A.add(12);
    A.add(11);
    A.add(10);


//    qDebug() << "asda" << A.height();
//    qDebug() << "asda" << A.countLeaf();
//    qDebug() << A.inTree(0);

//    qDebug() << A.greater();
//    A.remove(3);
//    qDebug() << A.height();

//    A.clear();
//    qDebug() << A.height();

    A.toString();

    return 0;
}
