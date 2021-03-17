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


void Ut::addJarat() {	//itt fogom beolvasni a fájlt
	string sor;
	int szam;
	int i = 0;
	int numbers[4];	//konstruktorhíváshoz ez tárolja a paramétereket


	ifstream fin("szoveg.txt");	//fájl megnyitása

	while (!fin.eof()) {	//fájl végéig vizsgálom
		for (i = 0; i < 4; i++) {	//kinullázom, hogy ne legyen memóriaszemét
			numbers[i] = 0;
		}

		getline(fin, sor);	//beolvas egy sort
		istringstream szamok(sor);	//adatfolyam lesz belõle
		i = 0;
		while (szamok >> szam) {
			numbers[i] = szam;	//ezek lesznek a konstruktor paraméterei
			i++;
		}

		if (numbers[3] == 0) {	// 3 paraméteres konstruktor hívása
			Jarat** tempJarat = new Jarat*[count + 1];
			for (int j = 0; j < count; j++) {	//az eddigi járatok maradnak
				tempJarat[j] = Jaratok[j]; //
			}
			tempJarat[count] = new Jarat(numbers[0], numbers[1]);	//a +1-edik helyre az új járat kerül
			count++;

			for (i = 0; i < count; i++) {
			}
			delete[] Jaratok;
			Jaratok = tempJarat;
		}
		else {
			Jarat** tempJarat = new Jarat*[count + 1];
			for (int j = 0; j < count; j++) {	//az eddigi járatok maradnak
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
	int DepthNum = 1;	//mélység számozása
	int act = 0;	//BFS algoritmus egyik ciklusához
	int i = 0;	//iteráció
	int ActStation = hova;	
	int Vizsgalt = 0;	//mennyit vizsgált már
	int k = 0;
	int* kiirat = NULL;	//kiíratáshoz tömb, mivel az eredményt fordítva kell kiírni

	Jarat** Visited = new Jarat*[count];
	Jarat** FromWhere = new Jarat*[count];
	int* Depth = new int[count];
	
	Vizsgalt = 0;
	for (int i = 0; i < count; i++) {//nulladik lépés: beszedjük azokat a járatokat, akik a célpontból elérhetõek
		if (Jaratok[i]->getFrom() == honnan) { Visited[Vizsgalt] = Jaratok[i]; Depth[Vizsgalt] = 1; Jaratok[i]->checkThis(); FromWhere[Vizsgalt] = NULL; Vizsgalt++; }
		if (Jaratok[i]->getTo() == honnan) { Visited[Vizsgalt] = Jaratok[i]; Depth[Vizsgalt] = 1; Jaratok[i]->checkThis(); FromWhere[Vizsgalt] = NULL; Vizsgalt++; }
	}

	while (Vizsgalt < count) {	//ha minden járat megvan, kész
		while (Depth[act] == DepthNum) {//ráálunk az azonos mélységû tagokra és azok szomszédait fogom ellenõrizni
			for (k = 0; k < count; k++) {	//itt pakolódnak a szomszédai
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

	for (k = 0; k < count; k++) {	//kiíratáshoz megfelelõ méretû tömb kell; a mélység alapján tudjuk mekkora
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