#pragma once
#ifndef GAME_H
#define GAME_H

#include "Labyrinth.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game {
private:
	Labyrinth maze;
	Player player;

	bool check_can_move(int x, int y);
	void add_item_player();
	void move_minotaur_helper(int m, int n);
public:
	Game(Labyrinth& m);

	Labyrinth& getMaze();
	Player& getPLayer();

	void setMaze(Labyrinth& m);
	void setPlayer(Player& p);

	bool move_player(char c);
	void move_minotaur();
	bool end_game();												// nakon svakog poteza proveri da li postoji R i I (ako nesta od ova dva ne postoji kraj igre je)

	friend ostream& operator<<(ostream& stream,  Game& obj);
};
#endif