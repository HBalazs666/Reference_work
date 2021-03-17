#include "ut.h"
#include "jarat.h"
#include "Variable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

Ut::Ut(int honnan = 0, int hova = 0) :honnan(honnan), hova(hova), count(0), Jaratok(NULL) {}

Ut::~Ut() {
	for (int i = 0; i < count; i++) {
		delete Jaratok[i];
	}
	delete[] Jaratok;
	Jaratok = NULL;
}


void Ut::addJarat() {	//itt fogom beolvasni a f�jlt
	string sor;
	int szam;
	int i = 0;
	int numbers[4];	//konstruktorh�v�shoz ez t�rolja a param�tereket


	ifstream fin("szoveg.txt");	//f�jl megnyit�sa

	while (!fin.eof()) {	//f�jl v�g�ig vizsg�lom
		for (i = 0; i < 4; i++) {	//kinull�zom, hogy ne legyen mem�riaszem�t
			numbers[i] = 0;
		}

		getline(fin, sor);	//beolvas egy sort
		istringstream szamok(sor);	//adatfolyam lesz bel�le
		i = 0;
		while (szamok >> szam) {
			numbers[i] = szam;	//ezek lesznek a konstruktor param�terei
			i++;
		}

		if (numbers[3] == 0) {	// 3 param�teres konstruktor h�v�sa
			Jarat** tempJarat = new Jarat*[count + 1];
			for (int j = 0; j < count; j++) {	//az eddigi j�ratok maradnak
				tempJarat[j] = Jaratok[j]; //
			}
			tempJarat[count] = new Jarat(numbers[0], numbers[1]);	//a +1-edik helyre az �j j�rat ker�l
			count++;

			for (i = 0; i < count; i++) {
			}
			delete[] Jaratok;
			Jaratok = tempJarat;
		}
		else {
			Jarat** tempJarat = new Jarat*[count + 1];
			for (int j = 0; j < count; j++) {	//az eddigi j�ratok maradnak
				tempJarat[j] = Jaratok[j]; //
			}

			tempJarat[count] = new Variable(numbers[0], numbers[1], numbers[2], numbers[3]);
			count++;
			for (i = 0; i < count; i++) {
			}
			delete[] Jaratok;

			Jaratok = tempJarat;
		}
		for (i = 0; i < 4; i++) {
			numbers[i] = 0;
		}
	}
	return;
}

void Ut::BFS() {
	int DepthNum = 1;	//m�lys�g sz�moz�sa
	int act = 0;	//BFS algoritmus egyik ciklus�hoz
	int i = 0;	//iter�ci�
	int ActStation = hova;	
	int Vizsgalt = 0;	//mennyit vizsg�lt m�r
	int k = 0;
	int* kiirat = NULL;	//ki�rat�shoz t�mb, mivel az eredm�nyt ford�tva kell ki�rni

	Jarat** Visited = new Jarat*[count];
	Jarat** FromWhere = new Jarat*[count];
	int* Depth = new int[count];
	
	Vizsgalt = 0;
	for (int i = 0; i < count; i++) {//nulladik l�p�s: beszedj�k azokat a j�ratokat, akik a c�lpontb�l el�rhet�ek
		if (Jaratok[i]->getFrom() == honnan) { Visited[Vizsgalt] = Jaratok[i]; Depth[Vizsgalt] = 1; Jaratok[i]->checkThis(); FromWhere[Vizsgalt] = NULL; Vizsgalt++; }
		if (Jaratok[i]->getTo() == honnan) { Visited[Vizsgalt] = Jaratok[i]; Depth[Vizsgalt] = 1; Jaratok[i]->checkThis(); FromWhere[Vizsgalt] = NULL; Vizsgalt++; }
	}

	while (Vizsgalt < count) {	//ha minden j�rat megvan, k�sz
		while (Depth[act] == DepthNum) {//r��lunk az azonos m�lys�g� tagokra �s azok szomsz�dait fogom ellen�rizni
			for (k = 0; k < count; k++) {	//itt pakol�dnak a szomsz�dai
				if (Jaratok[k]->getFrom() == Visited[act]->getFrom() && Jaratok[k]->getChecked() == 0) {
					Visited[Vizsgalt] = Jaratok[k];
					Depth[Vizsgalt] = DepthNum + 1;
					FromWhere[Vizsgalt] = Visited[act];
					Jaratok[k]->checkThis();
					Vizsgalt++;
				}
				if (Jaratok[k]->getFrom() == Visited[act]->getTo() && Jaratok[k]->getChecked() == 0) {
					Visited[Vizsgalt] = Jaratok[k];
					Depth[Vizsgalt] = DepthNum + 1;
					FromWhere[Vizsgalt] = Visited[act];
					Jaratok[k]->checkThis();
					Vizsgalt++;
				}
				if (Jaratok[k]->getTo() == Visited[act]->getFrom() && Jaratok[k]->getChecked() == 0) {
					Visited[Vizsgalt] = Jaratok[k];
					Depth[Vizsgalt] = DepthNum + 1;
					FromWhere[Vizsgalt] = Visited[act];
					Jaratok[k]->checkThis();
					Vizsgalt++;
				}
				if (Jaratok[k]->getTo() == Visited[act]->getTo() && Jaratok[k]->getChecked() == 0) {
					Visited[Vizsgalt] = Jaratok[k];
					Depth[Vizsgalt] = DepthNum + 1;
					FromWhere[Vizsgalt] = Visited[act];
					Jaratok[k]->checkThis();
					Vizsgalt++;
				}
			}
			act++;
		}
		DepthNum++;
	}

	for (k = 0; k < count; k++) {	//ki�rat�shoz megfelel� m�ret� t�mb kell; a m�lys�g alapj�n tudjuk mekkora
		if (Visited[k]->getTo() == hova) { DepthNum = Depth[k]; kiirat = new int[Depth[k] + 1];  break; }
		if (Visited[k]->getFrom() == hova) { DepthNum = Depth[k]; kiirat = new int[Depth[k] + 1]; break; }
	}
	kiirat[DepthNum] = hova; DepthNum--;
	cout << "Informaciok az erintett jaratokrol: " << endl;
	while (ActStation != honnan) {
		for (int h = 0; h < count; h++) {
			if (Visited[h]->getFrom() == ActStation) { ActStation = Visited[h]->getTo(); kiirat[DepthNum] = ActStation; DepthNum--; Visited[h]->printInfo(); break; }
			if (Visited[h]->getTo() == ActStation) { ActStation = Visited[h]->getFrom(); kiirat[DepthNum] = ActStation; DepthNum--; Visited[h]->printInfo(); break; }
		}
	}
	cout << "Az egyik legkevesebb atszallast tartalmazo utvonal:" << endl;
	for (i = 0; i <= Depth[k]; i++) {
		cout << kiirat[i] << endl;
	}
	delete[] kiirat;
	delete[] Visited;
	delete[] FromWhere;
}