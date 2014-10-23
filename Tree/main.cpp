#include <QDebug>
#include "Tree.h"
#include "Node.h"

//toString ainda não implementada

int main()
{
    Tree<int> A, B;

    B.add(20);
    B.add(15);
    B.add(14);
    B.add(16);

    Node<int> *temp = B.getTree();

    A.add(8);
    A.add(6);
    A.add(5);
    A.add(7);
    A.add(13);
    A.add(12);
    A.add(11);
    A.add(10);


    A.addSubTree(temp);

    qDebug() << "asda" << A.height();
    qDebug() << "asda" << A.countLeaf();
    qDebug() << A.inTree(0);

    qDebug() << A.greater();
    A.remove(3);
    qDebug() << A.height();

    A.clear();
    qDebug() << A.height();

    return 0;
}
