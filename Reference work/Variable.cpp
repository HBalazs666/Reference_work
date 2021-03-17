#include "Variable.h"
#include <iostream>

using namespace std;

Variable::Variable(int from, int to, int WiFi, int Class) :Jarat(from, to), WiFi(WiFi), Class(Class){}


int Variable::getFrom() {
	return from;
}

int Variable::getTo() {
	return to;
}

void Variable::printInfo() {
	cout << "A(z) " << from << ' ' << to << ' ';
	if (WiFi == 1 && Class == 0) { cout << "vonalon valaszthato szolgaltatas a WiFi elerhetoseg." << endl; }
	if (WiFi == 1 && Class == 1) { cout << "vonalon valaszthato szolgaltatasok a WiFi elerhetoseg es az Osztaly." << endl; }
	if (Class == 1 && WiFi == 0) { cout << "vonalon kivalaszthato az Osztaly." << endl; }
	if (WiFi == 0 && Class == 0) { cout << "vonalon nincsenek valaszthato szolgaltatasok." << endl; }
}