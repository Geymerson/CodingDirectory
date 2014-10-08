#ifndef LQUEUE_H
#define LQUEUE_H

#include "QueueADT.h"
#include "Link.h"
#include <QDebug>

template <typename E>
class LQueue: public Queue<E>
{
private:
    Link<E> * m_front;
    Link<E> * m_rear;
    int m_size;
public:
    LQueue() //Default Constructor
    {
        m_front = new Link<E>();
        m_rear = m_front;
        m_size = 0;
    }

    ~LQueue() //Default Destructor
    {
        clear();
        delete m_front;
    }

    void clear() //Clears the queue
    {
        while(m_front->next != 0)
        {
            m_rear = m_front->next;
            m_front->next = m_rear->next;
            delete m_rear;
        }
        qDebug() << m_front->next;
        m_rear = m_front;
        m_size = 0;
    }

    void enqueue(const E& it) //adds a item to the queue
    {
        Link<E> * temp = new Link<E>(it);
        m_rear->next = temp;
        m_rear = m_rear->next;
        m_size++;
    }

    E dequeue() // remove and return the value at queue's front
    {
        if(m_size == 0)
        {
            qDebug() << "Lista Vazia";
            return 0;
        }
        E it = m_front->next->content;
        Link<E> * temp = m_front->next;
        m_front->next = temp->next;
        if(m_rear == temp)
        {
            m_rear = m_front;
        }
        delete temp;
        m_size--;
        return it;
    }

    const E& frontValue() const //returns the value at queue's front
    {
        if(m_size == 0)
        {
            qDebug() << "Lista Vazia";
            return 0;
        }
        return m_front->next->content;
    }

    int length() const
    {
        return m_size;
    }
};

#endif // LQUEUE_H
