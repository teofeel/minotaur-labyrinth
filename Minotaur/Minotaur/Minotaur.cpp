// Minotaur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"
#include <chrono>

using namespace std;
using namespace std::chrono;


void input_number(int &value, string input_str) {
	do {
		cout << input_str;
		cin >> value;

		if (!cin) {
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		break;
	} while (true);
}

void gameplay(Game &game) {
	do {
		char c;
		cout << "Enter next move: ";
		cin >> c;

		if (c == 'q' || c == 'Q')
			break;

		if (!game.move_player(c)) {
			cin.clear();
			cin.ignore(1000,'\n');
			continue;
		}
			
		// move minotaur
		game.move_minotaur();
	
		//check game end
		if (game.end_game())
			break;

		cout << game << endl;

	} while (true);

	cout << game << endl;
	cout << "Game End" << endl;

}



void load_game() {
	int n;
	input_number(n, "Enter dimension n: ");

	int m;
	input_number(m, "Enter dimension m: ");

	int o;
	do {
		input_number(o, "Enter number of items (must be greater than 3): ");
	} while (!o || o < 3);
	

	auto start = high_resolution_clock::now();

	Labyrinth maze(n, m, o);

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "Duration to create maze: " << duration.count() << "ms"<< endl;

	Game game(maze);

	cout << game << endl;

	gameplay(game);
}

int main()
{
	load_game();
	
    return 0;
}

