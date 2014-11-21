#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include "Node.h"
#include <QByteArray>

int encoding(QString fileName);
void toString(Node<int> *tree, QByteArray *k);

#endif // ENCODING_H
