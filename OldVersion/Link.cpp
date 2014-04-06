#include "Link.h"

void Link::setNext(Link *x)
{
    next = x;
}
Link *Link::getNext()
{
    return next;
}
void Link::setPrev(Link *x)
{
    prev = x;
}
Link *Link::getPrev()
{
    return prev;
}
void Link::setVals(int x)
{
    vals = x;
}
int Link::getVals()
{
    return vals;
}
