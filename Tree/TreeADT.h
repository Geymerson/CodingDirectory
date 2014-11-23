#ifndef TREEBADT_H
#define TREEBADT_H

#include "Node.h"

template <typename E>
class BinTree {
public:
    BinTree() {} //Base constructor
    virtual ~BinTree(){} // Base destructor
    virtual void add(const E& item) = 0; //add in tree
    virtual void remove(E item) = 0;//Remove item from the tree
    virtual void clear() = 0;//Clean tree
    virtual bool inTree(E item) = 0;//checks if the item is in the tree
    virtual const E lower() = 0;// returns lower value
    virtual const E greater() = 0;//returns higher value
    virtual QString toString() = 0;// print tree
    virtual int countNode() const = 0;//returns number of nodes
    virtual int countLevel() const   = 0;//returns number of levels
    virtual int countLeaf() const = 0;//return number of leafs
    virtual int height() const = 0;//return size of tree
    virtual Node<E> *getTree() const = 0;// returns root
    virtual void addSubTree(Node<E> *node) = 0;//add sub tree
    virtual void toLeft() = 0; // Go left
    virtual void toRight() = 0;// Go right
    virtual E getHere() const = 0;// Return value current node
};

#endif // TREEBADT_H
