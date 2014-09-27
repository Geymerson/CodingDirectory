#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "list.h"
#include "Node.h"
#include <QDebug>

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

    void clear()
    {
        while(m_head != 0) //Check if the list isn't empty
        {
            m_cursor = m_head;
            m_head = m_head->next;
            delete m_cursor;
        }
        m_cursor = m_head;
        m_listSize = 0;
        m_position = 0;
    }

    void insert(const E& item) //insert an item after the current node
    {
        Node<E> * temp = new Node<E>(item);
        if(m_head == 0)
        {
            this->append(item);
        }
        else
        {
            temp->next = m_cursor->next;
            if(m_cursor == m_tail) //move tail to the right if an item was inserted at list's end
            {
                m_tail = temp;
            }
            m_cursor->next = temp;
            m_listSize++;
        }
    }

    void append(const E& item) //insert an item at list's end
    {
        Node<E> *node = new Node<E>(item);
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

    E remove() //removes the item at the current node
    {
        E content;
        Node<E> * temp;
        if(m_head == 0) //No change is made if the list is empty
        {
            return 0;
        }
        content = m_cursor->content;
        if(m_cursor == m_head) //move list's head to the right if head is the one being removed
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

    void moveToStart()
    {
        m_cursor = m_head;
        m_position = 1;
    }

    void moveToEnd()
    {
        m_cursor = m_tail;
        m_position = m_listSize;
    }

    void prev()
    {
        if(m_cursor != m_head)
        {
            int i;
            m_cursor = m_head;
            for(i = 1; i !=  (m_position - 1); i++)
            {
                m_cursor = m_cursor->next;
            }
            m_position = i;
        }
    }

    void next()
    {
        if(m_cursor != m_tail)
        {
            m_cursor = m_cursor->next;
            m_position++;
        }
    }

    int length() const
    {
        return m_listSize;
    }

    int currPos() const
    {
        return m_position;
    }

    void moveToPos(int pos)
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

    const E& getValue() const
    {
        Q_ASSERT_X(m_cursor != 0, "LinkedList::getValue", "Empty list");
        return m_cursor->content;

    }
};

#endif // LINKEDLIST_H
