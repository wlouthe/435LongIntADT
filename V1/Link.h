#ifndef LINK_H
#define LINK_H

class Link
{
public:
    Link *next;
    Link *prev;
    int vals;
    void setNext(Link *);
    Link *getNext();
    void setPrev(Link *);
    Link *getPrev();
    void setVals(int);
    int getVals();
};

#endif // LINK_H
