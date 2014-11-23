#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include "Node.h"
#include <QByteArray>
#include "LinkedList.h"

int encoding(QString fileName);
void treeRepresentation(Node<int> *tree, QByteArray *k);
void charCodification(Node<int> *tree, Node<int> *left, Node<int> *right,
                      QString *codification, LinkedList<QString> *list);

#endif // ENCODING_H
