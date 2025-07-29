#include "stdafx.h"
#include "MinotaurFigure.h"

using namespace std;

MinotaurFigure::MinotaurFigure(int ii, int jj) : Cell(ii, jj, 'M') {
	this->is_alive = true;
}

MinotaurFigure::MinotaurFigure() : Cell() {
	this->is_alive = true;
}

bool MinotaurFigure::getIsAlive() {
	return this->is_alive;
}

void MinotaurFigure::setIsAlive(bool alive) {
	this->is_alive = alive;
}