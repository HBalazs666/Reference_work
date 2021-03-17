#pragma once
#include "jarat.h"

class Ut {
	
	int honnan; //külsõ adat
	int count;	//dinamikus tömb méretét számolja
	int hova; //külsõ adat
	Jarat** Jaratok; //az összes járat
public:
	Ut(int honnan, int hova);
	~Ut();

	void addJarat(); //járatok tömbbe töltése fájlból
	void BFS();
};