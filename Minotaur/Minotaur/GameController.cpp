#include "stdafx.h"
#include "GameController.h"
#include "Game.h"
#include "GameSaver.h"
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
void GameController::input_number(int &value, string input_str) {
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
void GameController::gameplay(Game &game) {
	do {
		char c;
		cout << "Enter next move: ";
		cin >> c;

		if (c == 'q' || c == 'Q')
			break;

		if (!game.move_player(c)) {
			cout << "You can't move there" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
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
	GameSaver::getInstance().save_game(game, "game_result.txt");
}


/*
funkcija za ucitavanje igre (pravljenje lavirinta)
Opis:
korisnik unosi dimenzije matrice + broj predmeta u lavirintu kroz konzolu
nakon unosa pravi se lavirint i krece igra
*/
void GameController::load_game(char* argv[]) {
	int n = atoi(argv[1]);
	if (n < 15) return;
	//input_number(n, "Enter dimension n: ");

	int m = atoi(argv[2]);
	if (m < 15) return;
	//input_number(m, "Enter dimension m: ");

	int o = atoi(argv[3]);
	if (o < 3) return;
	if (o > 2 * (m + n)) return;

	auto start = high_resolution_clock::now();

	Labyrinth maze(n, m, o);

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << "Duration to create maze: " << duration.count() << " microseconds" << endl;

	Game game(maze);

	cout << game << endl;

	this->gameplay(game);
}