#pragma once

#include "stdafx.h"
#include "Labyrinth.h"
#include "Cell.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Player::add_powerup(Item& item) {
	if (item == "Fog of War") {
		this->cant_see = true;
	}
	else if (item == "Sword") {
		this->can_kill_minotaur = true;
	}
	else if (item == "Shield") {
		this->can_defend_from_minotaur = true;
	}
	else if (item == "Hammer") {
		this->can_move_wall = true;
	}
}

void Player::remove_powerup(Item& item) {
	if (item == "Fog of War") {
		this->cant_see = false;
	}
	else if (item == "Sword") {
		this->can_kill_minotaur = false;
	}
	else if (item == "Shield") {
		this->can_defend_from_minotaur = false;
	}
	else if (item == "Hammer") {
		this->can_move_wall = false;
	}
}




Player::Player(int ii, int jj, char type) : Cell(ii,jj,type) {
	this->can_defend_from_minotaur = false;
	this->can_kill_minotaur = false;
	this->can_move_wall = false;
	this->cant_see = false;
}

Player::Player(int ii, int jj) : Cell(ii, jj, 'R') {
	this->can_defend_from_minotaur = false;
	this->can_kill_minotaur = false;
	this->can_move_wall = false;
	this->cant_see = false;
}

Player::Player() : Cell() {
	this->can_defend_from_minotaur = false;
	this->can_kill_minotaur = false;
	this->can_move_wall = false;
	this->cant_see = false;
}



vector<Item> Player::getItems() {
	return this->items;
}

bool Player::getCanDefend() {
	return this->can_defend_from_minotaur;
}

bool Player::getCanKill() {
	return this->can_kill_minotaur;
}

bool Player::getCanMove() {
	return this->can_move_wall;
}

bool Player::getCantSee() {
	return this->cant_see;
}



void Player::addItem(Item item) {
	this->items.push_back(item);
	this->add_powerup(item);
}

void Player::setCanDefend(bool b) {
	this->can_defend_from_minotaur = b;
}

void Player::setCanKill(bool b) {
	this->can_kill_minotaur = b;
}

void Player::setCanMove(bool b) {
	this->can_move_wall = b;
}
void Player::setCantSee(bool b) {
	this->cant_see = b;
}



void Player::shorten_lifespan_items() {
	for (Item& item : this->items) {
		item.shorten_lifespan();
	}

	
}

void Player::remove_inactive_items() {
	vector<string> name_item;
	for (int i = 0; i < this->items.size(); i++) {

		if (this->items[i].getLifespan() <= 0) {
			this->remove_powerup(items[i]);
			name_item.push_back(items[i].getName());
			//this->items.erase(this->items.begin() + i);
		}
	}

	for (int i = 0; i < name_item.size(); i++) {
		for (int j = 0; j < this->items.size(); j++) {
			if (items[j].getName() == name_item[i]) {
				this->items.erase(this->items.begin() + j);
				break;
			}
		}
	}
}



ostream& operator<<(ostream& stream, const Player& obj) {
	cout << "Player items:" << endl;
	for (Item i : obj.items) {
		stream << i;
	}

	return stream;
}