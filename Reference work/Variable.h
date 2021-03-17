#pragma once
#include "jarat.h"

class Variable : public Jarat {
	int WiFi;
	int Class; 
public:
	Variable(int from, int to, int WiFi, int Class);
	int getFrom();
	int getTo();
	void printInfo();
};