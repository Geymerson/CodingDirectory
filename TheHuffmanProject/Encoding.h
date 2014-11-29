#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include "Node.h"
#include <QByteArray>
#include "LinkedList.h"

int encoding(QString fileName);

bool charCodification(Node<int> *tree, Node<int> *left,
                      Node<int> *right, QString aux[],
                      QString sample);

void treeRepresentation(Node<int> *tree, QByteArray *k);


#endif // ENCODING_H
