#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "Cell.h"
#include "Item.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player : public Cell {
private:
	vector<Item> items;
	bool can_defend_from_minotaur;	// kada dodje do pomeranja minotaura na plejera ako plejer ima shield minotaur mora drugi potez da napravi
	bool can_kill_minotaur;			// plejer moze da unisti minotaura
	bool can_move_wall;				// plejer moze da unisti zid
	bool cant_see;					// plejer ne moze da vidi ceo lavirint

	void add_powerup(Item& item);			// funkcija koja dodaje powerup playeru
	void remove_powerup(Item& item);		// funkcija koja brise powerup playeru
public:
	Player(int ii, int jj, char type);
	Player(int ii, int jj);
	Player();

	vector<Item> getItems();
	bool getCanDefend();
	bool getCanKill();
	bool getCanMove();
	bool getCantSee();

	void addItem(Item item);											// funkcija za dodavanje itema playeru
	void setCanDefend(bool b);
	void setCanKill(bool b);
	void setCanMove(bool b);
	void setCantSee(bool b);

	void shorten_lifespan_items();										// funkcija koja skracuje lifespan itemu
	void remove_inactive_items();										// ako im je lifespan na nuli, funkcija ga brise

	friend ostream& operator<<(ostream& stream, const Player& obj);

	~Player();
};

#endif