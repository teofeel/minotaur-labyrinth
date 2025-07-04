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

/*
	funkcija koja proverava da li je unos dobar
	parametri: 
		- int &value (referenca na value) 
		- string input_str (ispisuje se prilikom unosa)
	Opis:
		ova funkcija radi samo za numericke tipove
*/
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

/*
	funkcija za igranje igre
	Opis:
		kao parametar prima referencu na objekat klase Game
		korisnik unosom na tastaturu pomera robota
*/
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


/*
	funkcija za ucitavanje igre (pravljenje lavirinta)
	Opis:
		korisnik unosi dimenzije matrice + broj predmeta u lavirintu
		nakon unosa pravi se lavirint i krece igra
*/
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

