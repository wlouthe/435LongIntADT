#include <iostream>
#include "stdlib.h"
//#define NULL 0

using namespace std;


/*
 /////////////////////////////////////////////
 // Original "insertAfter" for DLL
 /////////////////////////////////////////////
 Link *tmp;
 if((pos)<=((mycount-1)-pos))
 {
 tmp = first;
 int tcount = 0;
 while(tcount != pos)
 {
 tmp = tmp->next;
 tcount++;
 }
 }
 else
 {
 tmp = last;
 int tcount = mycount-1;
 while(tcount != pos)
 {
 tmp = tmp->prev;
 tcount--;
 }
 }
 Link *newLink = new Link;
 tmp->next->prev = newLink;
 newLink->next = tmp->next;
 newLink->prev = tmp;
 tmp->next = newLink;
 newLink->VALUE = x;
 mycount++;
//*/


class Link
{
public:
    Link *next;
    Link *prev;
    int VALUE;
};

class DoublyLinkedList
{
    Link *first;
    Link *last;
public:
    DoublyLinkedList();
    Link *getFirst();
    Link *getLast();
    Link *getNext(Link *);
    Link *getPrev(Link *);
    void insertFirst(int);
    void insertLast(int);
    void insertAfter(int, Link *);
    void insertBefore(int, Link *);
    void removeFirst();
    void removeLast();
    void removeAfter(Link *);
    void removeBefore(Link *);
    int getValue(Link *);

};

class ListADT
{
    int mycount;
public:
    int GET_FIRST(); //return pos
    int GET_LAST(); //return pos
    int NEXT_RIGHT(int); //return pos, send pos
    int NEXT_LEFT(int); //return pos, send pos
    void INSERT_RIGHT(int); //send value
    void INSERT_LEFT(int); //send value
    bool IS_FIRST(int); //returns T/F, send pos
    bool IS_LAST(int); //returns T/F, send pos
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//// Begin DLL functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

DoublyLinkedList::DoublyLinkedList()
{
    last = first;
}

Link *DoublyLinkedList::getFirst()
{
    return first;
}
Link *DoublyLinkedList::getLast()
{
    return last;
}
Link *DoublyLinkedList::getNext(Link *pos)
{
    return pos->next;
}
Link *DoublyLinkedList::getPrev(Link *pos)
{
    return pos->prev;
}
void DoublyLinkedList::insertFirst(int x)
{
    if(first == NULL)
    {
        first = new Link;
        last = first;
        first->VALUE = x;
        first->next = NULL;
        first->prev = NULL;
        return;
    }
    first->prev = new Link;
    first->prev->next = first;
    first = first->prev;
    first->VALUE = x;
}
void DoublyLinkedList::insertLast(int x)
{
    if(last == NULL)
    {
        first = new Link;
        last = first;
        first->VALUE = x;
        first->next = NULL;
        first->prev = NULL;
        return;
    }
    last->next = new Link;
    last->next->prev = last;
    last = last->next;
    last->VALUE = x;
}
void DoublyLinkedList::insertAfter(int x, Link *pos)
{
    /*
     if pos is equal to last (or last is NULL from not being initialized or emptied) it will perform the insertLast function.
     if it is not equal to last or empty, it know that the current node exists and that a node after exists,
     allowing the new node to be placed between them.
    */
    if(pos == last)
    {
        insertLast(x);
        return;
    }
    Link *newLink = new Link;
    newLink->VALUE = x;
    newLink->prev = pos;
    newLink->next = pos->next;
    pos->next->prev = newLink;
    pos->next = newLink;
}
void DoublyLinkedList::insertBefore(int x, Link *pos)
{
    /*
     if pos is equal to first (or first is NULL from not being initialized or emptied) it will perform the insertFirst function.
     if it is not equal to first or empty, it know that the current node exists and that a node before exists,
     allowing the new node to be placed between them.
     */
    if(pos == first)
    {
        insertFirst(x);
        return;
    }
    Link *newLink = new Link;
    newLink->VALUE = x;
    newLink->next = pos;
    newLink->prev = pos->prev;
    pos->prev->next = newLink;
    pos->prev = newLink;
}

void DoublyLinkedList::removeFirst()
{
    if(first == NULL)
    {
        return;
    }
    if(first->next == NULL)
    {
        delete first;
        first = NULL;
        last = NULL;
        return;
    }
    Link *tmp = first;
    first = first->next;
    delete tmp;
}
void DoublyLinkedList::removeLast()
{
    if(last == NULL)
    {
        return;
    }
    if(last->prev == NULL)
    {
        delete last;
        first = NULL;
        last = NULL;
        return;
    }
    Link *tmp = last;
    last = last->prev;
    delete tmp;
}
void DoublyLinkedList::removeAfter(Link *pos)
{
    if(pos == NULL)
    {
        return;
    }
    if(pos->next == NULL)
    {
        return;
    }
    if(pos->next == last)
    {
        removeLast();
        return;
    }
    Link *tmp = pos->next;
    pos->next = pos->next->next;
    delete tmp;
}
void DoublyLinkedList::removeBefore(Link *pos)
{
    if(pos == NULL)
    {
        return;
    }
    if(pos->prev == NULL)
    {
        return;
    }
    if(pos->prev == first)
    {
        removeFirst();
        return;
    }
    Link *tmp = pos->prev;
    pos->prev = pos->prev->prev;
    delete tmp;
}

int DoublyLinkedList::getValue(Link *pos)
{
        return pos->VALUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//// Begin ListADT functions
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//// Begin Main Function
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int x;
    x = 16;
    DoublyLinkedList myDLL;
    myDLL.insertFirst(x);
    myDLL.insertFirst(23);
    myDLL.insertFirst(34);
    Link *mylink = myDLL.getFirst();
    while(mylink!=NULL)
    {
        cout << mylink->VALUE << endl;
        mylink = myDLL.getNext(mylink);
    }
    myDLL.removeFirst();
    mylink = myDLL.getFirst();
    while(mylink!=NULL)
    {
        cout << mylink->VALUE << endl;
        mylink = myDLL.getNext(mylink);
    }
    
    return 0;
}
