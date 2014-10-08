#include <QDebug>
#include "AStack.h"

int main()
{
    AStack<int> pilha;
    for(int i = 29; i >= 0; i--)
    {
        pilha.push(i);
       // qDebug() << pilha.topValue();
    }

    pilha.push(4);


    for(int i = pilha.length(); i >= 0; i--)
    {
        qDebug() << pilha.pop();
    }

    return 0;
}
