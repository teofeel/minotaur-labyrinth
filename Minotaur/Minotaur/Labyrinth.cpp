#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <stack>
#include <tuple>
#include "Labyrinth.h"
#include "Cell.h"

using namespace std;
std::mt19937 rng(std::random_device{}());

/*
	funkcija za kreiranje lavirinta/levela
	parametri: 
		- x,y (pocetna pozicija)
		- dx[] i dy[] (mogucnosti kretanja -> 4 mogucnosti: gore,desno,dole,levo)
	Opis:
		koristi DFS za generisanje lavirinta
		DFS probija zidove i pravi putove, izbor sledece pozicije za probijanje je random
*/
void Labyrinth::dfs(int x, int y, int dx[], int dy[]) {
	stack<pair<int, int>> s;
    s.push({x, y});

    while (!s.empty()) {
		int cx, cy;
		tie(cx, cy) = s.top();
        s.pop();

        vector<int> directions = {0, 1, 2, 3};
        //shuffle(directions.begin(), directions.end(), default_random_engine(rand()));
		shuffle(directions.begin(), directions.end(), rng);

        for (int d : directions) {
            int nx = cx + 2* dx[d];
            int ny = cy + 2* dy[d];

            if (nx >= 1 && nx < n-1 && ny >= 1 && ny < m-1 && matrix.at(nx).at(ny).getType() == '#') {
                matrix.at(cx + dx[d]).at(cy + dy[d]).setType(' ');
                matrix.at(nx).at(ny).setType(' ');

                s.push({nx, ny});
            }
        }
    }
}


/*
	funkcija koja proverava da li je moguce izaci iz lavirinta
	parametri: 
		- int entrance_x, entrance_y (ulaz, pocetna lokacija odakle krece potragu)
		- int exit_index (gde se nalazi izlaz)
		- int dx[], dy[] (mogucnosti kretanja -> 4 mogucnosti: gore,desno,dole,levo)
	Opis: 
		koristi dfs da pronadje izlaz
*/
bool Labyrinth::is_exit_reachable(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]) {
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	stack<pair<int, int>> to_visit;
	to_visit.push({ entrance_x, entrance_y });
	visited[entrance_x][entrance_y] = true;

	while (!to_visit.empty()) {
		int x, y;
		tie(x, y) = to_visit.top();
		to_visit.pop();

		if (matrix.at(x+1).at(y).getType() == 'I') {
			return true;
		}

		for (int d = 0; d < 4; ++d) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (nx >= 1 && nx < n - 1 && ny >= 1 && ny < m - 1 && (matrix.at(nx).at(ny).getType() == ' ' || matrix.at(nx).at(ny).getType()=='R') && !visited[nx][ny]) {
				visited[nx][ny] = true;
				to_visit.push({ nx, ny });
			}
		}
	}

	return false; 
}


/*
	funkcija za kreiranje minotaura i itema
	Opis:
		random se generise pozicija minotaura, ako je ta pozicija prazna na nju se postavlja minotaur
		isto vazi i za predmet, samo jos vodi racuna o broju predmeta i radi dok se svi ne generisu
*/
void Labyrinth::create_minotaur_items() {
	do {
		int minotaur_x = (rand() % (m - 2)) + 1;
		int minotaur_y = (rand() % (n - 2)) + 1;

		if (this->matrix.at(minotaur_y).at(minotaur_x).getType() == ' ') {
			this->matrix.at(minotaur_y).at(minotaur_x).setType('M');
			break;
		}
	} while (true);

	int items_number = this->items;
	do {
		int item_x = (rand() % (m - 2)) + 1;
		int item_y = (rand() % (n - 2)) + 1;

		if (this->matrix.at(item_y).at(item_x).getType() == ' ') {
			this->matrix.at(item_y).at(item_x).setType('P');
			items_number--;
		}
	} while (items_number > 0);

}

/*
	funkcija koja se brine o tome da postoji put do izlaza
	Parametri:
		- int entrance_x, entrance_y (ulaz, pocetna lokacija odakle krece potragu)
		- int exit_index (gde se nalazi izlaz)
		- int dx[], dy[] (mogucnosti kretanja -> 4 mogucnosti: gore,desno,dole,levo)
	Opis:
		samo ako se ne moze pronaci izlaz ova funkcija izvrsava svoju namenu
		probija se direktan put duz pravih linija do izlaza
		sve celije, sem izlaza, se postavljaju na ' '
*/
void Labyrinth::ensure_path_to_exit(int entrance_x, int entrance_y, int exit_index, int dx[], int dy[]) {
	if (!is_exit_reachable(entrance_x, entrance_y, exit_index, dx, dy)) {
		int current_x = entrance_x;
		int current_y = entrance_y;

		while (current_x != n-1 || current_y != exit_index) {
			if (current_x < n-1) current_x++;
			else if (current_x > n-1) current_x--;

			if (current_y < exit_index) current_y++;
			else if (current_y > exit_index) current_y--;

			matrix.at(current_x).at(current_y).setType(' ');
		}

		matrix.at(n - 1).at(exit_index).setType('I');
	}
}

/*
	funkcija koja probija zidove koji su celom duzinom/sirinom pune zidove
	Opis:
		u slucaju da algoritam ostavi neku sirinu/visinu celom duzinom pun zid, ova funkcija ce probiti
		probijanje se vrsi random, te celije se postavljaju da su ' '
	Napomena:
		pun zid se smatra jedino ako je '#'
*/
void Labyrinth::break_full_walls() {
	for (int i = 1; i < this->n-1; i++) {
		bool full_wall = true;

		for (int j = 1; j < this->m - 1; j++) {
			if (this->matrix.at(i).at(j).getType() != '#') {
				full_wall = false;
				break;
			}
		}

		if (full_wall) {
			int br = m - 2;
			while (br>0){
				bool crave_position = rand() % 2;
				if (crave_position) this->matrix.at(i).at(br).setType(' ');

				br--;
			}
		}
	}

	for (int j = 1; j < this->m - 1; j++) {
		bool full_wall = true;
		for (int i = 1; i < this->n - 1; i++) {
			if (this->matrix.at(i).at(j).getType() != '#') {
				full_wall = false;
				break;
			}
		}
		if (full_wall) {
			int br = n - 2;
			while (br>0) {
				bool crave_position = rand() % 2;
				if (crave_position) this->matrix.at(br).at(j).setType(' ');

				br--;
			}
		}
	}
}

/*
	funkcija za generisanje levela
	Opis:
		ova funkcija kreira game level
		postavlja ulaz, izlaz, robota
		poziva funkcije za kreiranje prolaza, minotaura, predmeta i provere
*/
void Labyrinth::create_matrix() {
	int entrance_index = (rand() % (m - 2))+1;
	int exit_index = (rand() % (m - 2)) + 1;
	
	matrix.at(0).at(entrance_index).setType('U');
	matrix.at(1).at(entrance_index).setType('R');
	matrix.at(n-1).at(exit_index).setType('I');

	int dx[] = {0,0,1,-1};
	int dy[] = {1,-1,0,0};

	this->dfs(1, entrance_index, dx, dy);
	this->break_full_walls();
	this->ensure_path_to_exit(1, entrance_index, exit_index, dx, dy);
	this->create_minotaur_items(); 

}



Labyrinth::Labyrinth(int nn, int mm, int o) {
	this->n = nn;
	this->m = mm;
	this->items = o;
	//this->matrix = vector<vector<Cell>>(n, vector<Cell>(m));
	for (int i = 0; i < n; i++) {
		vector<Cell> new_vector;
		this->matrix.push_back(new_vector);

		for (int j = 0; j < m; j++) {
			this->matrix.at(i).push_back(Cell(i, j, '#'));
		}
	}

	this->create_matrix();
}



int Labyrinth::getN() {
	return this->n;
}

int Labyrinth::getM() {
	return this->m;
}

int Labyrinth::getItems() {
	return this->items;
}

vector<vector<Cell>>& Labyrinth::getMaze() {
	return this->matrix;
}



void Labyrinth::setN(int nn) {
	this->n = nn;
}
void Labyrinth::setM(int mm) {
	this->m = mm;
}
void Labyrinth::setItems(int o) {
	this->items = o;
}


ostream& operator<<(ostream& stream, const Labyrinth& obj) {
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.m; j++) {
			stream << obj.matrix.at(i).at(j);
		}
		stream << endl;
	}

	return stream;
}

Labyrinth::~Labyrinth() {

}