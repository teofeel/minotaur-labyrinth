// Minotaur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"
#include "GameController.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


int main(int argc, char* argv[])
{
	if (argc < 4) {
		cout << "Not enough arguments\n" << endl;
		return 1;
	}
	
	GameController::getInstance().load_game(argv);
	
    return 0;
}

