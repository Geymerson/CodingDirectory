#include <QDebug>
#include "AStack.h"

int main()
{
    AStack<char> pilha;
    pilha.push('a'); //first in, last out
    pilha.push('b');
    pilha.push('c');
    pilha.push('d');
    pilha.push('e');
    pilha.toString();

    qDebug() << pilha.length();
    qDebug() << pilha.topValue();
    pilha.pop();
    qDebug() << pilha.topValue();
    pilha.push('f');
    qDebug() << pilha.topValue();
    qDebug() << pilha.length();

    qDebug() << pilha.toString();

//    AStack<int> pilha;

//    for(int i = 29; i >= 0; i--)
//    {
//        pilha.push(i);
//    }
//    pilha.push(4);
//    pilha.toString();

    return 0;
}
