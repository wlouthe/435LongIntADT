#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include "implementation.cpp"
using namespace std;

int main(int agrc, char  **argv)
{

	string a1("2222");
	string b1("99999999");
	string c1("246813575732");
	string d1("180270361023456789");

	//INIT THE LONG INTEGERS
	LongInt *a = new LongInt(); //= new LongInt();
	a->initialize(a1);
	LongInt *b = new LongInt();
	b->initialize(b1);
	LongInt *c = new LongInt();
	c->initialize(c1);
	LongInt *d = new LongInt();
	d->initialize(d1);

	//ADDITION TEST CASES
	LongInt *e = new LongInt();
	e = a->add(d);
    cout << "E = A + D = " ;
	e->print();
	LongInt *f = new LongInt();
	f = b->add(c);
    cout << "F = B + C = " ;
	f->print();
	LongInt *g = new LongInt();
	g = c->add(d);
	LongInt *h = new LongInt();
	h = e->add(e);
	LongInt *i = new LongInt();
	i = a->add(e);
	LongInt *j = new LongInt();
	j = b->add(g);
	LongInt *k = new LongInt();
	k = a->subtract(d);
	LongInt *l = new LongInt();
	l = c->subtract(d);
	LongInt *m = new LongInt();
	m = d->subtract(c);
	LongInt *n = new LongInt();
	n = h->subtract(h);
	LongInt *o = new LongInt();
	o = l->subtract(k);
	LongInt *p = new LongInt();
	p = j->subtract(m);
	LongInt *q = new LongInt();
	q = a->multiply(d);
	LongInt *r = new LongInt();
	r = b->multiply(c);
	LongInt *s = new LongInt();
	s = d->multiply(d);
	LongInt *t = new LongInt();
	t = k->multiply(e);
	LongInt *u = new LongInt();
	u = f->multiply(l);
	LongInt *v = new LongInt();
	v = i->multiply(j);

	//PRINT THE LONG INTEGERS
	cout << "ADDITION TEST CASES" << endl;
	cout << "E = A + D = " ;
	e->print();
	cout << "F = B + C = " ;
	f->print();
	cout << "G = C + D = " ;
	g->print();
	cout << "H = E + E = " ;
	h->print();
	cout << "I = A + E = " ;
	i->print();
	cout << "J = B + G = " ;
	j->print();
	cout << "SUBTRACTION TEST CASES" << endl;
	cout << "K = A - D = " ;
	k->print();
	cout << "L = C - D = " ;
	l->print();
	cout << "M = D - C = " ;
	m->print();
	cout << "N = H - H = " ;
	n->print();
	cout << "O = L - K = " ;
	o->print();
	cout << "P = J - M = " ;
	p->print();

	cout << "MULTIPLY TEST CASES" << endl;
	cout << "Q = A * D = " ;
	q->print();
	cout << "R = B * C = " ;
	r->print();
	cout << "s = D * D = " ;
	s->print();
	cout << "T = K * E = " ;
	t->print();
	cout << "U = F * L = " ;
	u->print();
	cout << "V = I * J = " ;
	v->print();
		

	//FREE THE MEMORY HELD THE LONG INTEGERS
	free(a); free(b); free(c); free(d); free(e); free(f); free(g); free(h); free(i); free(j); free(k); free(l);
	free(m); free(n); free(o); free(p); free(q); free(r); free(s); free(t); free(u); free(v);

	return 0;
}