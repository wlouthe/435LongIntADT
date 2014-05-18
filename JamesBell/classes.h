#include <iostream>
#include "stdlib.h"
class Node
{
	private:
		int val;
		Node *forward;
		Node *back;
		
		Node()
		{
			val = NULL;
            forward = NULL;
            back = NULL;
		}
		friend class ListADT;
};

class ListADT
{
	private:
		Node *head;
		Node *tail;

	public:
		ListADT();
		~ListADT();

		bool empty();
		bool is_first(Node* Node);
		bool is_last(Node* Node);

		void insert_left(int v);
		void insert_right(int v);
		Node* get_first();
		Node* get_last();
		int get_value(Node* Node);
		Node* next_left(Node* Node);
		Node* next_right(Node* Node);
		void print_Node(Node *n);


	protected:
		void push_Node(Node *v, int d);

	friend class LongInt;
};


class LongInt
{
	private:
		bool sign;
		ListADT *l;
	public:
		LongInt();
		~LongInt();
		void initialize(std::string s);
		char getsign();
		void setsign(char sign);
		void print();

		bool greaterthan(LongInt *&q);
		bool lessthan(LongInt *&q);
		bool equalto(LongInt *&q);
		bool abs(LongInt *&q);

		int digit(int t);
		int getdigitcount();
		int over_flow(int *t);

		LongInt* add(LongInt *&q);
		LongInt* subtract(LongInt *&q);
		LongInt* multiply(LongInt *&q);
		LongInt* power(LongInt *&q);
		LongInt* divide(LongInt *&q);
};