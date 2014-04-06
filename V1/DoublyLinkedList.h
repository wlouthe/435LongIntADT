#include "Link.h"
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

class DoublyLinkedList
{
    int mycount;
    Link *first;
    Link *last;
public:
    DoublyLinkedList();
    int getFirst();
    int getLast();
    int getNext(int);
    int getPrev(int);
    void insertFirst(int);
    void insertLast(int);
    void insertAfter(int, int);
    void insertBefore(int, int);
    int removeAt(int);
    int getValue(int);
    int getValue();

};

#endif // DOUBLYLINKEDLIST_INCLUDED
