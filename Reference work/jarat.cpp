#include "jarat.h"
#include <iostream>

using namespace std;

Jarat::Jarat(int from, int to): from(from), to(to), checked(0) {}

Jarat::~Jarat(){}

int Jarat::getChecked() {
	return checked;
}

void Jarat::checkThis() {
	this->checked = 1;
}

int Jarat::getFrom() {
	return from;
}

int Jarat::getTo() {
	return to;
}

void Jarat::printInfo() {
	cout << "A(z) " << from << ' ' << to << ' ' << "vonalon nincsenek valaszthato szolgaltatasok." << endl;
}