#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "Labyrinth.h"
#include "Cell.h"

using namespace std;

Cell::Cell(int ii, int jj) {
	this->i = ii;
	this->j = jj;
	this->type = '#';
}

Cell::Cell(int ii, int jj, char t) {
	this->i = ii;
	this->j = jj;
	this->type = t;
}

Cell::Cell() {
	this->i = 0;
	this->j = 0;
	this->type = ' ';
}

int Cell::getI() {
	return this->i;
}
int Cell::getJ() {
	return this->j;
}
char Cell::getType() {
	return this->type;
}


void Cell::setI(int ii) {
	this->i = ii;
}
void Cell::setJ(int jj) {
	this->j = jj;
}
void Cell::setType(char t) {
	this->type = t;
}


ostream& operator<<(ostream& stream, const Cell& obj) {
	stream << obj.type;
	return stream;
}

bool operator == (const Cell& obj1, const Cell& obj2) {
	return obj1.type == obj2.type;
}

bool operator == (const Cell& obj, const char& name) {
	return obj.type == name;
}

