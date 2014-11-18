#ifndef TREEBADT_H
#define TREEBADT_H

#include "Node.h"

template <typename E>
class BinTree {
public:
    BinTree() {} //Base constructor
    virtual ~BinTree(){} // Base destructor
    virtual void add(const E& item, const int& quantity) = 0; //add in tree
    virtual void clear() = 0;//Clean tree
    virtual const E lower() = 0;// returns lower value
    virtual const E greater() = 0;//returns higher value
    virtual int countLeaf() const = 0;//return number of leafs
    virtual int height() const = 0;//return size of tree
    virtual Node<E> *getTree() const = 0;// returns root
    virtual void addSubTree(Node<E> *node) = 0;//add sub tree
    virtual void toLeft() = 0; // Go left
    virtual void toRight() = 0;// Go right
    virtual E getNode() const = 0;// Return value current node
};

#endif // TREEBADT_H
