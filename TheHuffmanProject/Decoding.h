#ifndef DECODING_H
#define DECODING_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <Node.h>

void treeCreat(Node<char> *tree, QByteArray *treeRep);
int decoding(QString fileName);

#endif // DECODING_H
