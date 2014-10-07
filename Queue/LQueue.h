#ifndef LQUEUE_H
#define LQUEUE_H

#include "QueueADT.h"
#include "Link.h"

template <typename E>
class LQueue: public Queue<E>
{
private:
    Link<E> * m_front;
    Link<E> * m_rear;
    int m_size;
public:
    LQueue()
    {
        m_front = new Link<E>();
        m_rear = m_front;
        m_size = 0;
    }

    ~LQueue();

    void clear()
    {
        while(m_front->next != 0)
        {
            m_rear = m_front;
            m_front = m_front->next;
            delete m_rear;
        }
        m_size = 0;
        m_rear = m_front;
    }

    void enqueue(const E& it)
    {
        m_rear->next = Link<E> * temp = new Link(it);
        m_rear = m_rear->next;
        m_size++;
    }

    E dequeue()
    {
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

    const E& frontValue() const
    {
        return m_front->next->content;
    }

    int length() const
    {
        return m_size;
    }
};

#endif // LQUEUE_H
