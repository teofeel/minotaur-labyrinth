#pragma once
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Game.h"



class GameController{
private:
	GameController() = default;

	GameController(const GameController&) = delete;
	GameController& operator=(const GameController&) = delete;

	void input_number(int &value, string input_str);
	
public:
	static GameController& getInstance() {
		static GameController instance;
		return instance;
	}
	

	void load_game(char* argv[]);
	void gameplay(Game &game);
};

#endif