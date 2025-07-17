#pragma once
#ifndef GAMESAVER_H
#define GAMESAVER_H
#include "Game.h"
#include "Labyrinth.h"

class GameSaver {
private:
	GameSaver() = default;

	GameSaver(const GameSaver&) = delete;
	GameSaver& operator=(const GameSaver&) = delete;

	string get_winner(Game &game);
public:
	static GameSaver& getInstance() {
		static GameSaver instance;
		return instance;
	}

	void save_game(Game &game, string file_path);
};

#endif