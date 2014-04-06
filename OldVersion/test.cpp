#include <iostream>
#include "DoublyLinkedList.h"
#include "stdio.h"
#include "stdlib.h"
using namespace std;

int main()
{
	/*
	DoublyLinkedList *DLL = new DoublyLinkedList;
	DLL->insertFirst(16);
	cout << DLL->getFirst() << endl;
	cout << DLL->getValue(0) << endl;
	return 0;
	*/
	int x;
   	x = 16;
   	DoublyLinkedList myDLL;
   	myDLL.insertFirst(x);
   	cout << myDLL.getFirst() << myDLL.getValue(0);
    	return 0;
}
