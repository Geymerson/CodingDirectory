#include <QDebug>
#include "Tree.h"
#include "Node.h"

int main()
{
    Tree<int> A;

    A.add(5);
    A.add(2);
    A.add(9);
    A.add(3);
    A.add(7);
    A.add(1);

    qDebug() << "asda" << A.height();
    qDebug() << "asda" << A.countLeaf();
    qDebug() << A.inTree(0);

    A.remove(3);

    A.clear();
    return 0;
}
