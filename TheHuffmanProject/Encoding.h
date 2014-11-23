#ifndef ENCODING_H
#define ENCODING_H

#include <QString>
#include "Node.h"
#include <QByteArray>
#include "LinkedList.h"

int encoding(QString fileName);
void treeRepresentation(Node<int, int> *tree, QByteArray *k);
void charCodification(Node<int, int> *tree, Node<int, int> *left, Node<int, int> *right,
                      QString *codification, LinkedList<int, QString> *list);

#endif // ENCODING_H
