#include "stdafx.h"
#include "GameSaver.h"
#include "Game.h"
#include "Labyrinth.h"
#include <fstream>

using namespace std;

string GameSaver::get_winner(Game &g) {
	Labyrinth lab = g.getMaze();

	bool minotaur_alive = false;
	bool robot_alive = false;
	bool exit_found = false;

	for (int i = 0; i < lab.getN(); i++) {
		for (int j = 0; j < lab.getM(); j++) {
			if (lab.getMaze().at(i).at(j) == 'M')
				minotaur_alive = true;
			if (lab.getMaze().at(i).at(j) == 'R')
				robot_alive = true;
			if (lab.getMaze().at(i).at(j) == 'I')
				exit_found = true;
		}
	}

	if (minotaur_alive && !robot_alive) {
		return "Minotaur won, player has been killed\n";
	}
	else if (!minotaur_alive && robot_alive && !exit_found) {
		return "Player won, Minotaur killed and player escaped\n";
	}
	else if (minotaur_alive && robot_alive && !exit_found) {
		return "Player escaped\n";
	}
	
	return "Game ended\n";

}

void GameSaver::save_game(Game &game, string file_path) {
	ofstream outFile(file_path);

	if (!outFile) {
		cout << "There has been an error with saving" << endl;
		return;
	}
	string game_result = this->get_winner(game);

	outFile << game_result;
	outFile << game;

	outFile.close();
}