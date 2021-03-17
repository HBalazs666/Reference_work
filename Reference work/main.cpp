#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Variable.h"
#include "ut.h"
#include "jarat.h"

using namespace std;


int main(){
	int honnan;
	int hova;
	cout << "Add meg a kiindulasi pontot: "<<endl;
	cin >> honnan;
	cout << "Add meg a vegpontot: "<<endl;
	cin >> hova;
	Ut ujut(honnan,hova);	//egyetlen utat nézünk
	ujut.addJarat();	//beszedi az éleket
	ujut.BFS();	//az algoritmus m
	return 0;
}