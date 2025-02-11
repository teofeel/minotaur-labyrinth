// Minotaur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Item.h"
#include "Game.h"

using namespace std;

void gameplay(Game &game) {
	do {
		char c;
		cout << "Enter next move: ";
		cin >> c;

		if (c == 'q' || c == 'Q')
			break;

		if (!game.move_player(c))
			continue;

		// move minotaur

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
	cout << "Enter dimension m: ";
	cin >> n;

	int m;
	cout << "Enter dimension m: ";
	cin >> m;

	int o;
	cout << "Enter number of items (must be greater than 3): ";
	cin >> o;


	Labyrinth maze(n, m, o);

	Game game(maze);

	cout << game << endl;

	gameplay(game);
}

int main()
{
	Labyrinth lab(31,47, 3);

	cout << lab << endl;

	load_game();
	/*Player p(1, 42, 'R');

	Item i1("Fog of War");
	Item i2("Shield");

	p.addItem(i1);

	cout << p << endl;
	p.shorten_lifespan_items();
	p.addItem(i2);
	cout << p << endl;

	//p.shorten_lifespan_items();
	//p.shorten_lifespan_items();
	//p.shorten_lifespan_items();

	//p.remove_inactive_items();

	//cout << p << endl;

	Game g(lab);
	g.setPlayer(p);
	
	cout << g << endl;*/
	
	
    return 0;
}

