#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;

int main()
{
	DoublyLinkedList *DLL = new DoublyLinkedList;
	DLL->insertFirst(16);
	cout << DLL->getFirst() << endl;
	cout << DLL->getValue(0) << endl;
	return 0;
}
