#pragma once
#ifndef MINOTAURFIGURE_H
#define MINOTAURFIGURE_H

#include "Cell.h"

using namespace std;

class MinotaurFigure : public Cell {
private:
	bool is_alive;
public:
	MinotaurFigure(int ii, int jj);
	MinotaurFigure();

	bool getIsAlive();
	void setIsAlive(bool alive);
};
#endif