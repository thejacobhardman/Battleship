// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 12/8/19

#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

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

	vector<string> spaces;

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
							string space = to_string(yCoordinate) + to_string(xCoordinate + i);
							spaces.push_back(space);
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
								string space = to_string(yCoordinate) + to_string(xCoordinate - i);
								spaces.push_back(space);
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
							string space = to_string(yCoordinate + i) + to_string(xCoordinate);
							spaces.push_back(space);
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
								string space = to_string(yCoordinate - i) + to_string(xCoordinate);
								spaces.push_back(space);
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

string getPlayerGuess() {
	bool validInput = false;
	vector<char> container;
	const char COLUMNS[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	string userInput, playerGuess;

	while (!validInput) {
		container.clear();
		cout << "\nEnter the cell that you'd like to fire at: ";
		cin >> userInput;

		for (char& character : userInput) {
			container.push_back(character);
		}

		if (sizeof(container) == 2) {
			validInput = true;
			cout << container[0] << container[1] << endl;	
		}
		else {
			cout << "Please enter a valid cell." << endl;
		}

		if (validInput) {
			for (int i = 0; i < 10; i++) {
				if (container[0] == COLUMNS[i]) {
					validInput = true;
					break;
				}
			}
		}

		if (validInput) {
			try {
				int testNum = container[1];
			}
			catch (exception) {
				cout << "Please enter a valid cell." << endl;
				validInput = false;
			}
		}

		if (validInput) {
			int testNum = container[1];
			if (testNum < 1 || testNum > 10) {
				cout << "Please enter a valid cell." << endl;
				validInput = false;
			}
		}
	}

	playerGuess.append(to_string(container[0]));
	playerGuess.append(to_string(container[1]));

	return playerGuess;
}

int main()
{
	string userInput;
	bool isRunning = true;
	vector<Ship> ships;

	srand(time(NULL));

	while (isRunning) {

		cout << "Welcome to Battleship!\nPlease ensure that your console window is large enough to see the entire game." << endl;

		int playerHealth = 100, turnsLeft = 50, difficulty;

		bool userConfirm = false, gameOver = false, validInput = false;

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
		ships.push_back(aircraftCarrier);

		Ship battleship(5);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = battleship.placeShip();
			if (!validShipPos) {
				battleship = battleship.generateNewValues();
			}
		}
		ships.push_back(battleship);

		Ship destroyer(3);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = destroyer.placeShip();
			if (!validShipPos) {
				destroyer = destroyer.generateNewValues();
			}
		}
		ships.push_back(destroyer);

		Ship submarine(2);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = submarine.placeShip();
			if (!validShipPos) {
				submarine = submarine.generateNewValues();
			}
		}
		ships.push_back(submarine);

		Ship scout(1);
		validShipPos = false;
		while (!validShipPos) {
			validShipPos = scout.placeShip();
			if (!validShipPos) {
				scout = scout.generateNewValues();
			}
		}
		ships.push_back(scout);
#pragma endregion

		validInput = false;
		while (!validInput) {
			cout << "\nPlease select a difficulty: " << endl;
			cout << "(1) Easy: A walk in the park." << endl;
			cout << "(2) Medium: A decent challenge." << endl;
			cout << "(3) Hard: Nearly impossible." << endl;
			cout << "Enter the corresponding number to select your difficulty: ";
			cin >> userInput;
			validInput = true;

			try {
				difficulty = stoi(userInput);
				if (difficulty < 1 || difficulty > 3) {
					cout << "\nPlease enter a valid integer." << endl;;
					validInput = false;
				}
			}
			catch (exception) {
				cout << "\nPlease enter a valid integer." << endl;;
				validInput = false;
			}
		}

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

		while (!gameOver) {
			string playerGuess;

			for (auto ship = ships.begin(); ship != ships.end(); ++ship) {
				if (ship->status == "Destroyed") {
					ships.erase(ship);
				}
			}

			clearScreen();

			printBoard(board, aircraftCarrier, battleship, destroyer, submarine, scout);

			cout << endl << "    Health: " << playerHealth << "    Turns Remaining: " << turnsLeft << endl;

			playerGuess = getPlayerGuess();

			cout << playerGuess << endl << "Press any button to continue.";
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
