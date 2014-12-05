#ifndef DECODING_H
#define DECODING_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDebug>
#include <Node.h>
#include "HuffmanInfo.h"

void treeCreate(Node<char> *tree, QByteArray *treeRep);
int decoding(QString ioFileName[]);

#endif // DECODING_H
