#ifndef ASTACK_H
#define ASTACK_H

#include <QDebug>
#include <StackADT.h>
#include <QString>
#include <ctype.h>

template<typename E>
class AStack: public StackADT<E>
{
private:
    int m_maxSize = 40;
    int m_top;
    E * m_listArray;
public:
    AStack( )
    {
        m_listArray = new E[m_maxSize];
        m_top = 0;
    }

    ~AStack()
    {
        delete [] m_listArray;
    }

    void clear()
    {
        m_top = 0;
    }

    void push(const E& it)
    {
        if(m_top < (m_maxSize - 1))
        {
            m_listArray[m_top++] = it;
        }
        else //increases the size of the array if it's needed
        {
            m_maxSize += m_maxSize/4;
            E * temp = new E[m_maxSize];
            for(int i = 0; i < m_top; i++)
            {
                temp[i] = m_listArray[i];
            }
            delete m_listArray;
            m_listArray = temp;
            push(it);
        }
    }

    E pop()
    {
        if(m_top != 0)
        {
            return m_listArray[--m_top];
        }
        qDebug() << "Empty Stack";
        return 0;
    }

    const E& topValue() const
    {
        return m_listArray[m_top - 1];
    }

    int length() const
    {
       return m_top;
    }

    bool isEmpty()
    {
        if(m_top == 0)
        {
            return true;
        }
        return false;
    }

    QString toString()
    {
        QString temp, aux;
        if(isdigit(m_listArray[0]))//If not string, convert and append it to temp
        {
            for(int i = 0; i < m_top; i++)
            {
                temp.append(aux.setNum(m_listArray[i]));
                temp.append(' ');

                //The items are being printed
                // from the last-in to the first-in
                qDebug() << m_listArray[(m_top - 1) - i];
            }
        }
        else
        {
            for(int i = 0; i < m_top; i++)
            {
                temp.append(m_listArray[i]); //If not string, convert and append it to temp
                //temp.append(' ');
                qDebug() << m_listArray[(m_top - 1) - i];
            }
        }
        return temp; //There is no spaces between the items of temp
    }
};

#endif // ASTACK_H
