#pragma once
#ifndef GAME_H
#define GAME_H

#include "Labyrinth.h"
#include "Player.h"
#include "MinotaurFigure.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game {
private:
	Labyrinth maze;
	Player player;
	MinotaurFigure minotaur;

	bool check_can_move(int x, int y);								// provera mogucnosti kretanja za playera
	void add_item_player();											// dodavanje itema playeru, od ponudjenih mogucnosti odabere jednu i dodeli playeru
public:
	Game(Labyrinth& m);

	Labyrinth& getMaze();
	Player& getPlayer();

	void setMaze(Labyrinth& m);
	void setPlayer(Player& p);

	bool move_player(char c);										// pomeranje igraca
	void move_minotaur();											// pomeranje minotaura	
	
	bool end_game();												// nakon svakog poteza proveri da li postoji R i I (ako nesta od ova dva ne postoji kraj igre je)

	friend ostream& operator<<(ostream& stream,  Game& obj);


	~Game();
};
#endif