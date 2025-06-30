#pragma once
#ifndef LABYRINTH_h
#define LABYRINTH_h
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Cell.h"

using namespace std;

class Labyrinth {
private:
	int n;
	int m;
	int items;
	vector<vector<Cell>> matrix;
	
	void create_matrix();
	void dfs(int x, int y, int dx[], int dy[]);
	bool is_exit_reachable(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]);
	void ensure_path_to_exit(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]);
	void break_full_walls();
	void create_minotaur_items();
public:
	Labyrinth(int nn, int mm, int o);
	Labyrinth();

	int getN();
	int getM();
	int getItems();

	void setN(int nn);
	void setM(int mm);
	void setItems(int o);

	vector<vector<Cell>>& getMaze();

	friend ostream& operator<<(ostream& stream, const Labyrinth& obj);

	~Labyrinth();
};

#endif
