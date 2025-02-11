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

void Game::setPlayer(Player& p) {
	this->player = p;
}

bool Game::check_can_move(int x, int y) {
	if (this->maze.getMaze().at(x).at(y).getType() == '#')
		return false;
	else if (this->maze.getMaze().at(x).at(y).getType() == '#' && this->player.getCanMove())
		return true;

	return true;
}

void Game::add_item_player() {
	// random generise item
	vector<string> items = { "Fog of War", "Shield", "Sword", "Hammer"};
	srand(static_cast<unsigned>(time(nullptr)));

	int index = rand() % 4;

	this->player.addItem(items[index]);
}

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

	if (!this->check_can_move(x2, y2)) {
		cout << "You can't move there" << endl;
		return false;
	}

	// umanjimo lifespan orudja i izbacimo ona koja su gotova
	this->player.shorten_lifespan_items();
	this->player.remove_inactive_items();

	// proveri da li je minotaur na x2 y2
	if (this->maze.getMaze().at(x2).at(y2) == 'M' && !this->player.getCanKill()) {
		this->maze.getMaze().at(x1).at(y1).setType(' ');

	}
	// proveri da li je P na x2 y2
	else if (this->maze.getMaze().at(x2).at(y2) == 'P') {
		this->add_item_player();
	}

	// proveri da li je I na x2 y2

	this->maze.getMaze().at(x1).at(y1).setType(' ');
	this->maze.getMaze().at(x2).at(y2) = player;

	this->player.setI(x2);
	this->player.setJ(y2);

	return true;
}

void Game::move_minotaur() {
	// scan maze to find M

	// once found M save coordinates

	// check surrounding cells if there is wall or player

	// if player is near move to that cell

	// if not choose random cell to move

}

bool Game::end_game() {
	int br = 0;

	for (int i = 0; i < this->maze.getM(); i++) {
		for (int j = 0; j < this->maze.getN(); j++) {
			if (this->maze.getMaze().at(i).at(j) == 'R' || this->maze.getMaze().at(i).at(j) == 'I')
				br++;
		}
	}

	if (br < 2)
		return true;

	return false;
}



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