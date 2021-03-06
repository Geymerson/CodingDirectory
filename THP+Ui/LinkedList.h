#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListADT.h"
#include "Node.h"

template<class E>
class LinkedList : public List<E>
{
private:
    Node<E> *m_cursor;
    Node<E> *m_head;
    Node<E> *m_tail;
    int m_position;
    int m_listSize;
public:
    LinkedList() {
        m_cursor = 0;
        m_head = 0;
        m_tail = 0;
        m_listSize = 0;
        m_position = 0;
    }

    ~LinkedList() { this->clear(); }

    void clear()
    {
        while(m_head != 0) //Checks if the list isn't empty
        {
            m_cursor = m_head;
            m_head = m_head->next;
            delete m_cursor;
        }
        m_cursor = m_head;
        m_listSize = 0;
        m_position = 0;
    }

    void insert(const E& item, const int& count) //inserts an item after the current node
    {
        Node<E> * temp = new Node<E>(item, count);
        if(m_head == 0)
        {
            this->append(item, count);
        }
        else
        {
            temp->next = m_cursor->next;
            if(m_cursor == m_tail) //moves tail to the right if an item was inserted at list's end
            {
                m_tail = temp;
            }
            m_cursor->next = temp;
            m_listSize++;
        }
    }

    void append(const E& item, const int& count) //inserts an item at list's end
    {
        Node<E> *node = new Node<E>(item, count);
        if(m_head == 0)
        {
            m_head = node;
            m_tail = m_head;
            m_cursor = m_head;
            m_position++;
        }
        else
        {
            m_tail->next = node;
            m_tail = m_tail->next;
        }
        m_listSize++;
    }

    void pInsert(const E& item, const int& count, Node<E> *pointer)
    {
        Node<E> * temp = new Node<E>(item, count, pointer);
        if(m_head == 0)
        {
            this->pAppend(item, count, pointer);
        }
        else
        {
            temp->next = m_cursor->next;
            if(m_cursor == m_tail) //moves tail to the right if an item was inserted at list's end
            {
                m_tail = temp;
            }
            m_cursor->next = temp;
            m_listSize++;
        }
    }

    void pAppend(const E& item, const int& count, Node<E> *pointer)
    {
        Node<E> *node = new Node<E>(item, count, pointer);
        if(m_head == 0)
        {
            m_head = node;
            m_tail = m_head;
            m_cursor = m_head;
            m_position++;
        }
        else
        {
            m_tail->next = node;
            m_tail = m_tail->next;
        }
        m_listSize++;
    }

    E remove() //removes the item at the current node and return the value removed
    {
        E content;
        Node<E> *temp;
        if(m_head == 0) //No change is made if the list is empty
        {
            return 0;
        }
        content = m_cursor->content;
        if(m_cursor == m_head) //moves list's head to the right if head is the one being removed
        {
            m_head = m_head->next;
            delete m_cursor;
            m_cursor = m_head;
        }
        else
        {
            this->prev(); //cursor is moved one step left
            temp = m_cursor; //temp is now the one-step-left node
            m_cursor = m_cursor->next; //cursor is moved to it's original position
            temp->next = m_cursor->next;
            if(m_cursor == m_tail) //if list's tail is the one being removed, tail moves one step left
            {
                m_tail = temp;
            }
            delete m_cursor;
            m_cursor = temp;
        }
        m_listSize--;
        return content;
    }

    void moveToStart() //Sets cursor to list's start
    {
        m_cursor = m_head;
        m_position = 1;
    }

    void moveToEnd() //Sets cursor to list's end
    {
        m_cursor = m_tail;
        m_position = m_listSize;
    }

    void prev() //Moves the cursor one step left
    {
        if((m_head != 0) && (m_cursor != m_head))
        {
            int i = 1;
            m_cursor = m_head;
            while (i != (m_position - 1))
            {
                m_cursor = m_cursor->next;
                i++;
            }
            m_position = i;
        }
    }

    void next() //Moves the cursor one step right
    {
        if(m_cursor != m_tail)
        {
            m_cursor = m_cursor->next;
            m_position++;
        }
    }

    int length() const //returns list's size
    {
        return m_listSize;
    }

    int currPos() const //returns the current cursor's position
    {
        return m_position;
    }

    Node<E> *getCursor() const //return the current position pointer
    {
        return m_cursor;
    }

    Node<E> *getPointer() const //get the the pointer of the right children of the node
    {
        return m_cursor->right;
    }

    void moveToPos(int pos) //Moves to the position "pos"
    {
        Q_ASSERT_X((pos >= 1 && pos <= m_listSize), "LinkedList::getValue", "Empty list");
        int i;
        if(pos > m_position) //checks if the position intended to move is after the current position
        {
            for(i = m_position; i != pos; i++)
            {
                m_cursor = m_cursor->next;
            }
            m_position = i;
        }
        else
        {
            m_cursor = m_head;
            for(m_position = 1; m_position != pos; m_position++)
            {
                m_cursor = m_cursor->next;
            }
        }
    }

    const E& getValue() const //Gets the value of the current node
    {
        Q_ASSERT_X(m_cursor != 0, "LinkedList::getValue", "Empty list");
        //qDebug() << m_cursor->quantity << ';' <<m_cursor->content;
        return m_cursor->content;
    }

    const int& getQuantity() const //Gets the value of the current node
    {
        Q_ASSERT_X(m_cursor != 0, "LinkedList::getValue", "Empty list");
        //qDebug() << m_cursor->quantity << ';' <<m_cursor->content;
        return m_cursor->quantity;
    }

    bool seekValue(const E& value)
    {
        Node<E> *temp = m_head;
        int aux = 1;
        while(temp != 0)
        {
            if(temp->content == value)
            {
                m_position = aux;
                m_cursor = temp;
                return true;
            }
            temp = temp->next;
            aux++;
        }
        return false;
    }

    void bubbleSort()
    {
        int aux1;
        E aux2;
        Node<E> *aux3;
        Node<E> *temp = m_head;

        bool swap = true;

        if(temp == 0)
        {
            return;
        }

        while(swap)
        {
            swap = false;
            while(temp->next != 0)
            {
                aux1 = temp->quantity;
                aux2 = temp->content;
                aux3 = temp->right;

                if(temp->quantity >= temp->next->quantity)
                {
                    if(temp->quantity == temp->next->quantity)
                    {
                        if(temp->content > temp->next->content)
                        {
                            temp->quantity = temp->next->quantity;
                            temp->content = temp->next->content;
                            temp->right = temp->next->right;

                            temp->next->quantity = aux1;
                            temp->next->content = aux2;
                            temp->next->right = aux3;

                            swap = true;
                        }
                    }
                    else
                    {
                        temp->quantity = temp->next->quantity;
                        temp->content = temp->next->content;
                        temp->right = temp->next->right;

                        temp->next->quantity = aux1;
                        temp->next->content = aux2;
                        temp->next->right = aux3;

                        swap = true;
                    }
                }
                temp = temp->next;
            }
            temp = m_head;
        }
    }

    void swap(int pos1, int pos2)//pos1 < pos2, pos1 > 1, pos2 < list.length
    {
        if(pos1 >= pos2 || pos1 < 1 || pos2 > this->length())
        {
            return;
        }

        Node<E> *tempCursorPos = this->getCursor(); //saving the current cursor position
        this->moveToPos(pos1);
        Node<E> *temp1 = this->getCursor();

        E aux1 = temp1->content;
        int aux2 = temp1->quantity;
        Node<E> *aux3 = temp1->right;

        this->moveToPos(pos2);

        temp1->content = m_cursor->content;
        temp1->quantity = m_cursor->quantity;
        temp1->right = m_cursor->right;

        m_cursor->content = aux1;
        m_cursor->quantity = aux2;
        m_cursor->right = aux3;

        m_cursor = tempCursorPos;
        return;
    }
};

#endif // LINKEDLIST_H
