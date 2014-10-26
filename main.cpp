/*
 * #############################################################
 * #														   #
 * #	....::: Developed by Miroslaw Sondej - IV CT :::....   #
 * #                                                           #
 * #			    !!! All right reserved !!!                 #
 * #                                                           #
 * #############################################################
 */

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

//-------------------------------------------------
const int MAP_SIZE = 10;
int map[MAP_SIZE][MAP_SIZE];
//  map    [y]      [x]

//-------------------------------------------------
#ifdef _WIN32
	#define clearConsole() system("cls");
#else
	#define clearConsole() system("clear");
#endif

void clearMap();
void spawnShip(const int type);
void generateMap();
void displayMap();
bool isAnyShipLeft();

//=================================================
int main() {
	srand(time(NULL));
	clearMap();
	generateMap();

	bool gameover = false;
	int x = 0;
	int y = 0;
	int score = 0;
	unsigned int gametime = time(NULL);

	while(!gameover) {
		clearConsole();
		displayMap();

		cout << endl << "Podaj cel (x y) np. '5 2': ";
		cin >> x;
		cin >> y;

		while(true) {

			if(x < 0 || x > 9 || y < 0 || y > 9) {
				cout << endl << "Pole poza zakresem! Wybierz inne (koordynaty z zakresu 0-9): ";
				cin >> x;
				cin >> y;
			} else if(map[y][x] == 0) {
				map[y][x] = -2;
				score -= 5;
				break;
			} else if(map[y][x] > 0) {
				map[y][x] = -1;
				score += 50;
				break;
			} else {
				cout << endl << "To pole juz bylo ostrzelane! Wybierz inne: ";
				cin >> x;
				cin >> y;
			}
		}

		if(!isAnyShipLeft()) {
			gameover = true;
		}

		gametime = time(NULL)-gametime;
	}

	clearConsole();
	cout << "Koniec gry!" << endl;
	cout << "Zdobyles " << score << " punktow w czasie: " << gametime << "sekund" << endl;
	getchar();
	return 0;
}
//=================================================
void clearMap() {
	for(int i = 0; i < MAP_SIZE; i++)
		for(int j = 0; j < MAP_SIZE; j++)
			map[i][j] = 0;
}
//=================================================
void spawnShip(const int type) {
	/* a == 0     ***
	 *
	 * a == 1     *
	 * 			  *
	 * 			  *
	 */
	int x = 0;
	int y = 0;
	int a = 0;
	bool clear;

	while(true) {
		clear = true;

		x = random()%10;
		y = random()%10;
		a = random()%2;


		if(a == 0) {
			for(int i = (y-1); i <= (y+1); i++) {
				for(int j = (x-1); j <= (x+type); j++) {
					if(i < 0 || i > 9) continue;
					if(j < 0 || j > 9) clear = false;
					if(clear && map[i][j] != 0) clear = false;
				}
			}
		} else {
			for(int i = (x-1); i <= (x+1); i++) {
				for(int j = (y-1); j <= (y+type); j++) {
					if(i < 0 || i > 9) continue;
					if(j < 0 || j > 9) clear = false;
					if(clear && map[j][i] != 0) clear = false;
				}
			}
		}

		if(clear) {
			if(a == 0)
				for(int i = 0; i < type; i++)
					map[y][x+i] = type;
			else
				for(int i = 0; i < type; i++)
					map[y+i][x] = type;

			break;
		}
	}

}
//=================================================
void generateMap() {
	/*
	 * 	COUNT OF SHIPS:
	 *  	x1 - 4
	 * 		x2 - 3
	 * 		x3 - 2
	 * 		x4 - 1
	 */

	/*                      */ spawnShip(4);
	for(int i = 0; i < 2; i++) spawnShip(3);
	for(int i = 0; i < 3; i++) spawnShip(2);
	for(int i = 0; i < 4; i++) spawnShip(1);
}
//=================================================
void displayMap() {
	cout << "   0 1 2 3 4 5 6 7 8 9" << endl << endl;
	for(int i = 0; i < 10; i++) {
		cout << i << "  ";
		for(int j = 0; j < 10; j++) {
			switch(map[i][j]) {
				case -1: {
					cout << "# ";
					break;
				}
				case -2: {
					cout << ". ";
					break;
				}
				default: {
						cout << "* ";
					break;
				}

			}
		}
		cout << endl;
	}
}
//=================================================
bool isAnyShipLeft() {
	for(int i = 0; i < MAP_SIZE; i++)
		for(int j = 0; j < MAP_SIZE; j++)
			if(map[i][j] > 0) return 1;

	return 0;
}
//=================================================
