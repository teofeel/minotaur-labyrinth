#pragma once
#ifndef LABYRINTH_h
#define LABYRINTH_h
#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Cell.h"


class Labyrinth {
private:
	int n;
	int m;
	int items;
	vector<vector<Cell>> matrix;
	
	void create_matrix();																					// funkcija za generisanje levela
	void dfs(int x, int y, int dx[], int dy[]);																// funkcija za kreiranje matrice 
	bool is_exit_reachable(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]);				// funkcija koja proverava da li je moguce izaci iz lavirinta
	void ensure_path_to_exit(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]);			// funkcija koja se brine o tome da postoji put do izlaza
	void break_full_walls();																				// funkcija koja probija zidove koji su celom duzinom/sirinom pune zidove
	void create_minotaur_items();																			// funkcija za kreiranje minotaura i itema
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
