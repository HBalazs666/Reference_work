#pragma once
#include "jarat.h"

class Ut {
	
	int honnan; //k�ls� adat
	int count;	//dinamikus t�mb m�ret�t sz�molja
	int hova; //k�ls� adat
	Jarat** Jaratok; //az �sszes j�rat
public:
	Ut(int honnan, int hova);
	~Ut();

	void addJarat(); //j�ratok t�mbbe t�lt�se f�jlb�l
	void BFS();
};