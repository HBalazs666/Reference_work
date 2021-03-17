#pragma once

class Jarat {
protected:
	int from; //kiindul�si hely
	int to;	//c�lpont
	int checked; //arra kell, hogy egy �l ne szerepelhessen egyn�l t�bbsz�r

public:
	Jarat(int from, int to);
	virtual ~Jarat();

	int getChecked();
	void checkThis();	//arra kell, hogy egy �l ne szerepelhessen egyn�l t�bbsz�r
	virtual int getFrom();
	virtual int getTo();
	virtual void printInfo();
};