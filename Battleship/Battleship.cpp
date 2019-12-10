// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 12/8/19

#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>

using namespace std;

char board[10][10] = {
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
};

class Ship {
	int generateShipX() {
		int x = rand() % 9 + 0;
		return x;
	}

	int generateShipY() {
		int y = rand() % 9 + 0;
		return y;
	}

	bool generateShipOrientation() {
		int num = rand() % 2 + 1;

		switch (num) {
		case 1:
			return true;
			break;
		case 2:
			return false;
			break;
		}
	}

public:
	Ship(int);

	int length, 
		xCoordinate = generateShipX(), 
		yCoordinate = generateShipY();

	string status = getShipStatus();

	bool isShipHorizontal = generateShipOrientation();

	Ship generateNewValues() {
		Ship newShip(length);
		return newShip;
	}

	bool placeShip() {
		bool validShipPos = false;
		while (!validShipPos) {
			bool verificationPassed = true;
			if (isShipHorizontal) {
				if (xCoordinate <= length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate][xCoordinate + i] != ' ') {
							return false;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate][xCoordinate + i] = 'S';
						}
						return true;
					}
				}
				else {
					for (int i = 0; i < length; i++) {
						for (int i = 0; i < length; i++) {
							if (board[yCoordinate][xCoordinate - i] != ' ') {
								return false;
							}
						}
						if (verificationPassed == true) {
							for (int i = 0; i < length; i++) {
								board[yCoordinate][xCoordinate - i] = 'S';
							}
							return true;
						}
					}
				}
			}
			else {
				if (yCoordinate <= length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate + i][xCoordinate] != ' ') {
							return false;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate + i][xCoordinate] = 'S';
						}
						return true;
					}
				}
				else {
					for (int i = 0; i < length; i++) {
						for (int i = 0; i < length; i++) {
							if (board[yCoordinate - i][xCoordinate] != ' ') {
								return false;
							}
						}
						if (verificationPassed == true) {
							for (int i = 0; i < length; i++) {
								board[yCoordinate - i][xCoordinate] = 'S';
							}
							return true;
						}
					}
				}
			}
		}
	}

	string getShipStatus() {
		bool isShipDestroyed = false;

		if (isShipDestroyed) {
			return "Destroyed";
		}
		else {
			return "Active";
		}
	}
};

Ship::Ship(int lengthInput)
{
	length = lengthInput;
}

// I got this method to clear the console screen in C++ from: https://stackoverflow.com/a/5866648/10190341
void clearScreen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void printBoard(char board[10][10], Ship aircraftCarrier, Ship battleship, Ship destroyer, Ship submarine, Ship scout) {
	char letterArr[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 0) {
				cout << "| " << board[i][j] << " | ";
			}
			else {
				cout << board[i][j] << " | ";
			}
		}
		cout << letterArr[i];
		if (i == 1) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "		Ship Statuses:" << endl;
		}
		else if (i == 2) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	   Aircraft Carrier: " << aircraftCarrier.status << endl;
		}
		else if (i == 3) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	     Battleship: " << battleship.status << endl;
		}
		else if (i == 4) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << " 	      Destroyer: " << destroyer.status << endl;
		}
		else if (i == 5) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	      Submarine: " << submarine.status << endl;
		}
		else if (i == 6) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "             Scout Ship: " << scout.status << endl;
		}
		else if (i != 9) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << endl;
		}
	}
	cout << endl << "-----------------------------------------" << endl << "  1   2   3   4   5   6   7   8   9  10" << endl;
}

int main()
{
	string userInput;
	bool isRunning = true;

	srand(time(NULL));

	while (isRunning) {

		cout << "Welcome to Battleship!" << endl;

		int playerHealth = 100, turnsLeft = 50, difficulty;

		bool userConfirm = false, gameOver = false;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				board[i][j] = ' ';
			}
		}

#pragma region Generate Ships
		Ship aircraftCarrier(7);
		bool validShipPos = false;
		while (!validShipPos) {
			validShipPos = aircraftCarrier.placeShip();
			if (!validShipPos) {
				aircraftCarrier = aircraftCarrier.generateNewValues();
			}
		}

		Ship battleship(5);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = battleship.placeShip();
			if (!validShipPos) {
				battleship = battleship.generateNewValues();
			}
		}

		Ship destroyer(3);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = destroyer.placeShip();
			if (!validShipPos) {
				destroyer = destroyer.generateNewValues();
			}
		}

		Ship submarine(2);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = submarine.placeShip();
			if (!validShipPos) {
				submarine = submarine.generateNewValues();
			}
		}

		Ship scout(1);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = scout.placeShip();
			if (!validShipPos) {
				scout = scout.generateNewValues();
			}
		}
#pragma endregion

		userConfirm = false;
		while (!userConfirm) {
			cout << "Please select a difficulty: " << endl;
			cout << "(1) Easy: A walk in the park." << endl;
			cout << "(2) Medium: A decent challenge." << endl;
			cout << "(3) Hard: Nearly impossible." << endl;
			cout << "Enter the corresponding number to select your difficulty: ";
			cin >> difficulty;

			switch (difficulty) {
			case 1:
				playerHealth = 200;
				turnsLeft = 100;
				break;
			case 2:
				playerHealth = 100;
				turnsLeft = 50;
				break;
			case 3:
				playerHealth = 50;
				turnsLeft = 25;
				break;
			}

			userConfirm = true;
		}

		while (!gameOver) {
			clearScreen();

			printBoard(board, aircraftCarrier, battleship, destroyer, submarine, scout);

			cout << endl << "    Health: " << playerHealth << "    Turns Remaining: " << turnsLeft << endl;

			cout << "\nPress any button to continue." << endl;
			cin >> userInput;
		}

		userConfirm = false;
		while (!userConfirm) {
			cout << "Would you like to play again? (Y/N): ";
			cin >> userInput;

			if (userInput == "Y" || userInput == "y") {
				userConfirm = true;
			}
			else if (userInput == "N" || userInput == "n") {
				userConfirm = true;
				isRunning = false;
			}
			else {
				cout << "Please enter a valid selection." << endl;
			}
		}
	}
}
