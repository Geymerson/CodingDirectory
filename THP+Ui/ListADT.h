// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

#include "Node.h"

template <typename E> class List { // List ADT
private:
    //void operator =(const List&) {}      // Protect assignment
    List(const List&) {}           // Protect copy constructor
public:
    List() {}          // Default constructor
    virtual ~List() {} // Base destructor
    
    //Clear contents from the list, to make it empty.
    virtual void clear() = 0;
    
    // Insert an element at the current location.
    // item: The element to be inserted
    virtual void insert(const E& item, const int& count) = 0;

    // Insert an element at the current location.
    // item: The element to be inserted
    // count: The number of times that that item has appeared
    // pointer: A pointer to be pointed by "current->right" of the current list node
    virtual void pInsert(const E& item, const int& count, Node<E> *pointer) = 0;
    
    // Append an element at the end of the list.
    // item: The element to be appended.
    virtual void append(const E& item, const int& count) = 0;

    // Append an element at the end of the list.
    // item: The element to be appended.
    // count: The number of times that that item has appeared
    // pointer: A pointer to be pointed by "current->right" of the current list node
    virtual void pAppend(const E& item, const int& count, Node<E> *pointer) = 0;
    
    // Remove and return the current element.
    // Return: the element that was removed.
    virtual E remove() = 0;
    
    // Set the current position to the start of the list
    virtual void moveToStart() = 0;
    
    // Set the current position to the end of the list
    virtual void moveToEnd() = 0;
    
    // Move the current position one step left. No change
    // if already at beginning.
    virtual void prev() = 0;
    
    // Move the current position one step right. No change
    // if already at end.
    virtual void next() = 0;
    
    // Return: The number of elements in the list.
    virtual int length() const = 0;
    
    // Return: The position of the current element.
    virtual int currPos() const = 0;

    //Return: The cursor position
    virtual Node<E> *getCursor() const = 0;

    //Return: "current->right"
    virtual Node<E> *getPointer() const = 0;
    
    // Set current position.
    // pos: The position to make current.
    virtual void moveToPos(int pos) = 0;
    
    // Return: The current element.
    virtual const E& getValue() const = 0;

    //Seeks for the value in the list and returns true if it was found.
    //If value is not in the list, return false
    virtual bool seekValue(const E& value) = 0;

    // Return: The current element quantity.
    virtual const int& getQuantity() const = 0;

    //Sort the list using the Bubble Sort algorithm
    virtual void bubbleSort() = 0;

    //swaps position1 with position2
    //pos1 must be bigger than pos2s
    virtual void swap(int pos1, int pos2) = 0;
};
