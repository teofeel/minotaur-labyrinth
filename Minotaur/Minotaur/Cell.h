#pragma once
#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell {
protected:
	int i;
	int j;
	char type;
public:
	Cell(int ii, int jj);
	Cell(int ii, int jj, char t);
	Cell();

	int getI();
	int getJ();
	char getType();

	void setI(int ii);
	void setJ(int jj);
	void setType(char t);


	friend ostream& operator<<(ostream& stream, const Cell& obj);
	friend bool operator == (const Cell& obj1, const Cell& obj2);
	friend bool operator == (const Cell& obj, const char& name);
	

	~Cell();
};

#endif
