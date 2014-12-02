#ifndef ENCODING_H
#define ENCODING_H

#include <QFile>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include "Node.h"
#include "LinkedList.h"


int encoding(QString fileName);

void charCodification(Node<int> *tree, Node<int> *left,
                      Node<int> *right, QString aux[],
                      QString sample);

void treeRepresentation(Node<int> *tree, QByteArray *k);


#endif // ENCODING_H
