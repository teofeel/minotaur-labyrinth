#pragma once
#include "stdafx.h"
#include "Labyrinth.h"
#include "Cell.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>   
#include <ctime>

using namespace std;



Game::Game(Labyrinth& m) : maze(m), player() {
	for (int i = 0; i < this->maze.getN(); i++) {
		
		for (int j = 0; j < this->maze.getM(); j++) {
			
			if (maze.getMaze().at(i).at(j) == 'R') {
				this->player.setI(i);
				this->player.setJ(j);
				this->player.setType('R');
			}
		}
	}
}

Labyrinth& Game::getMaze() {
	return this->maze;
}

Player& Game::getPlayer() {
	return this->player;
}

void Game::setPlayer(Player& p) {
	this->player = p;
}

/*
	pomocna funkcija za proveru pomeranja player-a
	parametri: 
		- x i y (pozicija na koju player oce da se pomeri)
	povratna vrednost:
		- bool
	ako player ima cekic onda mu se omogucava prolaz kroz zid
*/
bool Game::check_can_move(int x, int y) {
	if (this->maze.getMaze().at(x).at(y).getType() == '#' && this->player.getCanMove())
		return true;
	else if (this->maze.getMaze().at(x).at(y).getType() == '#')
		return false;
		

	return true;
}

/*
	funkcija za generisanje predmeta igracu
	Opis:
		random se odabere predmet koji ce generisati igracu 
		onda se dodaje playeru pomocu metode addItem(Item item)
*/
void Game::add_item_player() {
	// random generise item
	vector<string> items = { "Fog of War", "Shield", "Sword", "Hammer"};
	srand(static_cast<unsigned>(time(nullptr)));

	int index = rand() % 4;

	this->player.addItem(items[index]);
}

/*
	funkcija za pomeranje igraca
	parametri: 
		- char c (unos sa tastature)
	povratna vrednost: 
		- bool
	opis:
		provera koji je karakter, mogucnost pomeranja igraca na tu poziciju
		nakon toga se izvrse propratne metode playera vezane za predmete
		i na kraju se player pomeri
*/
bool Game::move_player(char c) {
	int x1 = this->player.getI();
	int y1 = this->player.getJ();
	int x2, y2;

	if (c == 'W' || c == 'w') {
		x2 = x1 - 1;
		y2 = y1;
	}else if (c == 'S' || c == 's') {
		x2 = x1 + 1;
		y2 = y1;
	}
	else if (c == 'A' || c == 'a') {
		x2 = x1;
		y2 = y1-1;
	}
	else if (c == 'D' || c == 'd') {
		x2 = x1;
		y2 = y1+1;
	}
	else {
		return false;
	}

	if (!this->check_can_move(x2, y2)) {
		return false;
	}

	// umanjimo lifespan orudja i izbacimo ona koja su gotova
	this->player.shorten_lifespan_items();
	this->player.remove_inactive_items();

	// proveri da li je minotaur na x2 y2
	if (this->maze.getMaze().at(x2).at(y2) == 'M' && !this->player.getCanKill()) {
		this->maze.getMaze().at(x1).at(y1).setType(' ');
		return true;
	}

	// proveri da li je P na x2 y2
	if (this->maze.getMaze().at(x2).at(y2) == 'P') {
		this->add_item_player();
	}


	this->maze.getMaze().at(x1).at(y1).setType(' ');
	this->maze.getMaze().at(x2).at(y2) = player;

	this->player.setI(x2);
	this->player.setJ(y2);

	return true;
}

/*
	Pomocna funkcija za pomeranje minotaura
	Parametri: 
		-m,n (pozicija minotaura)
	Opis:
		generisanje novih mogucih pozicija za minotaura i provera pomneranja minotaura na njih
		ako se player nalazi do minotaura i moze da ga ubije, pomera se na tu
		na kraju se od mogucih pozicija koje su prosle uslove bira jedna
*/
void Game::move_minotaur_helper(int m, int n) {
	vector<pair<int, int>> new_coordinates = { {m + 1, n}, {m - 1,n}, {m, n + 1}, {m, n-1} };
	vector<int> remove_indexes;

	for (int i = 0; i < new_coordinates.size(); i++) {
	
		if (new_coordinates.at(i).first <= 0 || new_coordinates.at(i).first >= this->maze.getM()
			|| new_coordinates.at(i).second <= 0 || new_coordinates.at(i).second >= this->maze.getN()) {
			remove_indexes.push_back(i);
			continue;
		}
			
		// check surrounding cells if there is wall or player
		if (this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second) == '#') {
			remove_indexes.push_back(i);
			continue;
		}
		if (this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second) == 'M') {
			remove_indexes.push_back(i);
			continue;
		}


		// if player is near move to that cell
		if (this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second) == 'R' && this->player.getCanDefend()) {
			remove_indexes.push_back(i);
			continue;
		}
		/*else if (this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second) == 'R' && this->player.getCanDefend()) {
			remove_indexes.push_back(i);
			continue;
		}*/
		else if (this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second) == 'R') {
			this->maze.getMaze().at(m).at(n).setType(' ');
			this->maze.getMaze().at(new_coordinates.at(i).first).at(new_coordinates.at(i).second).setType('M');

			return;
		}
	}

	for (int i = remove_indexes.size()-1; i >= 0; i--) {
		new_coordinates.erase(new_coordinates.begin() + remove_indexes.at(i));
	}

	// if not choose random cell to move
	int new_coordinates_len = new_coordinates.size();
	int pair = rand() % new_coordinates_len;
	this->maze.getMaze().at(m).at(n).setType(' ');

	this->maze.getMaze().at(new_coordinates.at(pair).first).at(new_coordinates.at(pair).second).setType('M');

}

/*
	funkcija za pomeranje minotaura
	Opis:
		prvo pronadje minotaura u lavirintu 
		zatim prosledi njegove parametre pomocnoj za pomeranje minotaura
*/
void Game::move_minotaur() {
	// scan maze to find M
	for(int i=0; i< this->maze.getN(); i++){
		for (int j = 0; j < this->maze.getM(); j++) {
			if (this->maze.getMaze().at(i).at(j) == 'M') {
				// once found M save coordinates
				move_minotaur_helper(i, j);
				return;
			}

		}
	}
}


/*
	funkcija koja proverava kraj igre
	povratna vrednost: 
		-bool
	Opis:
		funkcija pretrazi da li postoje R ili I
		ako jedan od njih ne postoji vraca true (kraj igre)
*/
bool Game::end_game() {
	int br = 0;

	for (int i = 0; i < this->maze.getN(); i++) {
		for (int j = 0; j < this->maze.getM(); j++) {
			if (this->maze.getMaze().at(i).at(j) == 'R' || this->maze.getMaze().at(i).at(j) == 'I') {
				
				br++;
			}
				
		}
	}

	if (br < 2)
		return true;

	return false;
}


/*
	overload operatora za ispis
	Opis:
		ako player ima maglu rata, smanjuje ispis matrice lavirinta na 3x3 oko playera
		u suprotnom ispisuje celu
		ispisuje i predmete + njihov lifespan
*/
ostream& operator<<(ostream& stream, Game& obj) {
	if (obj.player.getCantSee()) {
		// potrebno uzeti podmatricu 3x3 tako da je player u sredini (maks jedan red iznad/ispod, levo/desno u zavisnosti od pozicije)
		int startX = obj.player.getI()-1, startY = obj.player.getJ() - 1;
		int endX = startX + 3, endY = startY + 3;

		for (int i = startX; i < endX; i++) {
			
			if (i >= obj.maze.getM()) {
				continue;
			}

			for (int j = startY; j < endY; j++) {
				stream << obj.maze.getMaze().at(i).at(j);
			}
			stream << endl;
		}
		stream << obj.player << endl;

		return stream;
	}

	stream << obj.maze;
	stream << obj.player;

	return stream;
}

Game::~Game() {

}