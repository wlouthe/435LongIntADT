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

DoublyLinkedList::DoublyLinkedList()
{
    last = first;
}

int DoublyLinkedList::getFirst(){
    return first->vals;
}
int DoublyLinkedList::getLast(){
    return last->vals;
}
void DoublyLinkedList::insertFirst(int x){
    if(first == NULL)
    {
        first = new Link;
        last = first;
        first->vals = x;
        mycount++;
        return;
    }
    first->prev = new Link;
    first->prev->next = first;
    first = first->prev;
    first->vals = x;
    mycount++;
}
void DoublyLinkedList::insertLast(int x){
    if(last == NULL)
    {
        first = new Link;
        last = first;
        first->vals = x;
        mycount++;
        return;
    }
    last->next = new Link;
    last->next->prev = last;
    last = last->next;
    last->vals = x;
    mycount++;
}
void DoublyLinkedList::insertAfter(int x, int pos){
    if(pos<=0)
    {
        insertFirst(x);
        return;
    }
    if(pos>=mycount-1)
    {
        insertLast(x);
        return;
    }
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
    newLink->vals = x;
    mycount++;
}
void DoublyLinkedList::insertBefore(int x, int pos){
    if(pos<=0)
    {
        insertFirst(x);
    }
    if(pos>=mycount-1)
    {
        insertLast(x);
    }
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
    tmp->prev->next = newLink;
    newLink->next = tmp;
    newLink->prev = tmp->prev;
    tmp->prev = newLink;
    newLink->vals = x;
    mycount++;
}
int DoublyLinkedList::removeAt(int pos){
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
    int tmpvals = tmp->vals;
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    return tmpvals;
}
int DoublyLinkedList::getValue(int pos)
{
    //return 12345;
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
    return tmp->vals;
}



int main()
{
    int x;
    x = 16;
    DoublyLinkedList myDLL;
    myDLL.insertFirst(x);
    cout << myDLL.getFirst() << myDLL.getValue(0);
    return 0;
}
