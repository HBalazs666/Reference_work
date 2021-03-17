#pragma once

class Jarat {
protected:
	int from; //kiindulási hely
	int to;	//célpont
	int checked; //arra kell, hogy egy él ne szerepelhessen egynél többször

public:
	Jarat(int from, int to);
	virtual ~Jarat();

	int getChecked();
	void checkThis();	//arra kell, hogy egy él ne szerepelhessen egynél többször
	virtual int getFrom();
	virtual int getTo();
	virtual void printInfo();
};