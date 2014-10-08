#ifndef LINK_H
#define LINK_H

template<typename E>
class Link
{
public:
    Link(){ this->next = 0; }
    Link(E content) {
        this->content = content;
        this->next = 0;
    }
    E content;
    Link * next;
};

#endif // LINK_H
