#include <QDebug>
#include "Tree.h"

int main()
{
    Tree<int> A;

    A.add(5);
    A.add(2);
    A.add(9);
    A.add(3);
    A.add(7);

    qDebug() << "asda" << A.height();
    qDebug() << "asda" << A.countLeaf();

    A.clear();
    return 0;
}
