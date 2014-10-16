#ifndef TREEBADT_H
#define TREEBADT_H

//onde tem Node substituir pela classe de vocês caso nome seja diferente
//onde tem Node substituir pela classe de você caso nome seja diferente

#include "Node.h"

template <typename E>
class BinTree {
public:

    //Base constructor
    BinTree() = 0;

//    //Constructor with sub tree
//    BinTree(Node left, Node right) = 0;

    virtual ~BinTree() = 0; // Base destructor

    //add in tree
    virtual void add(const E& item) = 0;

    //Remove item from the tree
    virtual void remove(E item) = 0;

    //Clean tree
    virtual void clear() = 0;

    //checks if the tree is
    virtual bool inTree(E item) = 0;

    // return lower value
    virtual const E lower() = 0;

    //return higher value
    virtual const E greater() = 0;

    // print tree
    virtual QString toString() = 0;

    //return number node
    virtual int countNode() const = 0;

    //return number level
    virtual int countLevel() const = 0;

    //return number leaf
    virtual int countLeaf() const = 0;

    //return size of tree
    virtual int length() const = 0;

//    // return root
//    virtual BinTree getTree();

    //add sub tree
    virtual void addSubTree(const Node<E>& node) = 0;

     // Go left
    virtual void toLeft() = 0;

    // Go right
    virtual void toRight() = 0;

    // Return value current node
    virtual E getHere() const = 0;
};

#endif // TREEBADT_H
