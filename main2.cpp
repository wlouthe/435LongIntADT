#include <iostream>
#include "stdlib.h"

using namespace std;

class Link
{
public:
    Link *next;
    Link *prev;
    int vals;
};

class ListADT
{
    Link *first;
    Link *last;
public:
    int nodeCount;
    ListADT();
    Link *GET_LAST();
    Link *GET_FIRST();
    Link *NEXT_RIGHT(Link *);
    Link *NEXT_LEFT(Link *);
    void INSERT_RIGHT(int);
    void INSERT_LEFT(int);
    bool IS_FIRST(Link *);
    bool IS_LAST(Link *);
    
};

ListADT::ListADT()
{
    nodeCount = 0;
    this->first = NULL;
    this->last = NULL;
}

Link *ListADT::GET_LAST()
{
    if(nodeCount == 0)
    {
        return NULL;
    }
    else
    {
        return this->last;
    }
}

Link *ListADT::GET_FIRST()
{
    if(nodeCount == 0)
    {
        return NULL;
    }
    else
    {
        return this->first;
    }
}
Link *ListADT::NEXT_RIGHT(Link *tmp)
{
    if(tmp!=NULL)
    {
        return tmp->next;
    }
    return NULL;
}
Link *ListADT::NEXT_LEFT(Link *tmp)
{
    if(tmp!=NULL)
    {
        return tmp->prev;
    }
    return NULL;
}
void ListADT::INSERT_RIGHT(int vals)
{
    Link *tmp;
    tmp->vals = vals;
    if(this->first == NULL)
    {
        this->first = tmp;
        this->last = this->first;
        nodeCount++;
        return;
    }
    this->last->next = tmp;
    tmp->prev = this->last;
    this->last = tmp;
    nodeCount++;
    
}
void ListADT::INSERT_LEFT(int vals)
{
    Link *tmp;
    tmp->vals = vals;
    if(this->first == NULL)
    {
        this->first = tmp;
        this->last = this->first;
        nodeCount++;
        return;
    }
    this->first->prev = tmp;
    tmp->next = this->first;
    this->first = tmp;
    nodeCount++;
}
bool ListADT::IS_FIRST(Link *tmp)
{
    return true;
}
bool ListADT::IS_LAST(Link *tmp)
{
    cout << &this->last << " : " << &tmp;
    return true;
}



int main()
{
    /*
     int x;
     x = 16;
     DoublyLinkedList *myDLL = new DoublyLinkedList;
     myDLL->insertFirst(x);
     cout << myDLL->getFirst() << myDLL->getValue(0);
     */
    ListADT myList;
    myList.INSERT_RIGHT(2);
    //myList.INSERT_RIGHT(4);
    //myList.INSERT_RIGHT(6);
    //myList.INSERT_RIGHT(8);
    //Link *tmp = myList.GET_FIRST();
    cout << myList.nodeCount;
    //cout << tmp->vals;
    return 0;
}
