#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include "Node.h"


int encoding(QString fileName);
QByteArray toString(Node<int> *tree, QByteArray k);

#endif // ENCODING_H
