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
		int x = rand() % 10;
		return x;
	}

	int generateShipY() {
		int y = rand() % 10;
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

	bool isShipHorizontal = generateShipOrientation();

	//debug method
	void printSpaces() {
		cout << "Ship Spaces: " << endl;
		for (int i = 0; i < spaces.size(); i++) {
			cout << spaces[i] << endl;
		}
	}

	bool checkIfHit(vector<int> playerCoordinates) {
		bool isShipHit = false;
		string userInput;

		string playerGuess = to_string(playerCoordinates[0] - 1) + to_string(playerCoordinates[1] - 1);

		int index = 0;
		for (int i = 0; i < spaces.size(); i++) {
			if (playerGuess == spaces[i]) {
				isShipHit = true;
				spaces[i].erase();
				index = i;
				break;
			}
		}

		if (isShipHit) {
			for (int i = index; i < spaces.size(); i++) {
				if (i != spaces.size() - 1) {
					spaces[i] = spaces[i + 1];
				}
			}
			spaces.resize(spaces.size() - 1);
		}

		printSpaces();
		cout << "spaces.size(): " << spaces.size() << endl;
		cin >> userInput;

		return isShipHit;
	}

	Ship generateNewValues() {
		Ship newShip(length);
		return newShip;
	}

	bool placeShip() {
		bool validShipPos = false;
		while (!validShipPos) {
			bool verificationPassed = true;
			if (isShipHorizontal) {
				if (xCoordinate <= 10 - length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate][xCoordinate + i] != ' ') {
							verificationPassed = false;
							return verificationPassed;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate][xCoordinate + i] = 'S';
							string space = to_string(yCoordinate) + to_string((xCoordinate + i));
							spaces.push_back(space);
						}
						return verificationPassed;
					}
				}
				else if (xCoordinate >= length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate][xCoordinate - i] != ' ') {
							verificationPassed = false;
							return verificationPassed;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate][xCoordinate - i] = 'S';
							string space = to_string(yCoordinate) + to_string((xCoordinate - i));
							spaces.push_back(space);
						}
						return verificationPassed;
					}
				}
				else {
					verificationPassed = false;
					return verificationPassed;
				}
			}
			else {
				if (yCoordinate <= 10 - length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate + i][xCoordinate] != ' ') {
							verificationPassed = false;
							return verificationPassed;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate + i][xCoordinate] = 'S';
							string space = to_string((yCoordinate + i)) + to_string(xCoordinate);
							spaces.push_back(space);
						}
						return true;
					}
				}
				else if (yCoordinate >= length) {
					for (int i = 0; i < length; i++) {
						if (board[yCoordinate - i][xCoordinate] != ' ') {
							return false;
						}
					}
					if (verificationPassed == true) {
						for (int i = 0; i < length; i++) {
							board[yCoordinate - i][xCoordinate] = 'S';
							string space = to_string((yCoordinate - i)) + to_string(xCoordinate);
							spaces.push_back(space);
						}
						return verificationPassed;
					}
				}
				else {
					verificationPassed = false;
					return verificationPassed;
				}
			}
		}
	}

	string getShipStatus() {
		bool isShipDestroyed = false;

		if (spaces.size() == 0) {
			isShipDestroyed = true;
		}

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

void printWelcome() {
	cout << "Welcome to Battleship!\nPlaying in full screen is reccomended." << endl;
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
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	   Aircraft Carrier: " << aircraftCarrier.getShipStatus() << endl;
		}
		else if (i == 3) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	     Battleship: " << battleship.getShipStatus() << endl;
		}
		else if (i == 4) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << " 	      Destroyer: " << destroyer.getShipStatus() << endl;
		}
		else if (i == 5) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "	      Submarine: " << submarine.getShipStatus() << endl;
		}
		else if (i == 6) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << "             Scout Ship: " << scout.getShipStatus() << endl;
		}
		else if (i != 9) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << endl;
		}
	}
	cout << endl << "-----------------------------------------" << endl << "  1   2   3   4   5   6   7   8   9  10" << endl;
}

string getPlayerGuess(vector<string> alreadyGuessedCoordinates) {
	bool validInput = false, validSize = false, guessedTen = false;
	vector<char> container;
	const char COLUMNS[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	string userInput, playerGuess;

	while (!validInput) {
		// Clear the container and get the user's input
		container.clear();
		cout << "\nEnter the cell that you'd like to fire at: ";
		cin >> userInput;

		// Add the user's input to the container
		for (char& character : userInput) {
			container.push_back(character);
		}

		// Check to make sure that the user entered 2 characters with a special clause for 3 if the user entered 10
		if (container.size() == 2) {
			validSize = true;
		}
		else if (container.size() == 3) {
			if (container[1] == '1' && container[2] == '0' && container.size() == 3) {
				validSize = true;
				guessedTen = true;
			}
			else {
				cout << "Please enter a valid cell." << endl;
			}
		}
		else {
			cout << "Please enter a valid cell." << endl;
		}

		// Check that the first character that the user entered is a valid letter
		if (validSize) {
			for (int i = 0; i < 10; i++) {
				if (container[0] == COLUMNS[i]) {
					validInput = true;
					break;
				}
			}

			if (!validInput) {
				cout << "Please enter a valid cell." << endl;
			}
		}

		// Check that the second character that the user entered is an integer
		if (validInput) {
			try {
				int testNum = container[1] - '0';
			}
			catch (exception) {
				cout << "Please enter a valid cell." << endl;
				validInput = false;
			}
		}

		// Check that the int that the user entered is between 1 and 10
		if (validInput) {
			int testNum = container[1] - '0';
			if (testNum < 1 || testNum > 10) {
				cout << "Please enter a valid cell." << endl;
				validInput = false;
			}
		}

		if (validInput) {
			// Convert the user's input to coordinates
			switch (container[0]) {
			case 'A':
				container[0] = '1';
				break;
			case 'B':
				container[0] = '2';
				break;
			case 'C':
				container[0] = '3';
				break;
			case 'D':
				container[0] = '4';
				break;
			case 'E':
				container[0] = '5';
				break;
			case 'F':
				container[0] = '6';
				break;
			case 'G':
				container[0] = '7';
				break;
			case 'H':
				container[0] = '8';
				break;
			case 'I':
				container[0] = '9';
				break;
			case 'J':
				container[0] = '0';
				break;
			}

			playerGuess += container[0];
			playerGuess += container[1];
			if (guessedTen) {
				playerGuess += container[2];
			}
		}

		//Check to make sure that the user hasn't guessed this space before
		if (validInput) {
			for (int i = 0; i < alreadyGuessedCoordinates.size(); i++) {
				if (playerGuess == alreadyGuessedCoordinates[i]) {
					playerGuess.clear();
					validInput = false;
					cout << "You cannot guess the same space twice." << endl;
					break;
				}
			}
		}
	}

	cout << "Player Guess: " << playerGuess << endl;

	return playerGuess;
}

int main()
{
	string userInput;
	bool isRunning = true;

	srand(time(NULL));

	while (isRunning) {
		clearScreen();

		printWelcome();

		int playerScore = 0, turnsLeft = 50, difficulty, scoreMultiplier = 1;

		vector<string> alreadyGuessedCoordinates;

		bool userConfirm = false, gameOver = false, validInput = false, gameWon = false;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				board[i][j] = ' ';
			}
		}

#pragma region Generate Ships
		vector<Ship> ships;

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
			turnsLeft = 100;
			scoreMultiplier = 1;
			break;
		case 2:
			turnsLeft = 50;
			scoreMultiplier = 2;
			break;
		case 3:
			turnsLeft = 25;
			scoreMultiplier = 3;
			break;
		}

		while (!gameOver) {
			string playerGuess;
			vector<int> playerCoordinates;
			bool isShipHit = false;

			vector<string> destroyedShips;
			for (auto ship = ships.begin(); ship != ships.end(); ++ship) {
				if (ship->getShipStatus() == "Destroyed") {
					destroyedShips.push_back(ship->getShipStatus());
				}
			}

			if (destroyedShips.size() == 5) {
				gameOver = true;
			}

			clearScreen();

			if (!gameOver) {
				printBoard(board, aircraftCarrier, battleship, destroyer, submarine, scout);

				cout << endl << "     Score: " << playerScore << "    Turns Remaining: " << turnsLeft << endl;
				cout << "Destroyed Ships: " << destroyedShips.size() << endl;

				playerGuess = getPlayerGuess(alreadyGuessedCoordinates);
				alreadyGuessedCoordinates.push_back(playerGuess);

				for (int i = 0; i < playerGuess.size(); i++) {
					int num = int(playerGuess[i] - '0');
					playerCoordinates.push_back(num);
				}

				if (playerCoordinates[0] == 0) {
					playerCoordinates[0] = 10;
				}

				if (playerCoordinates.size() == 3) {
					playerCoordinates[1] = 10;
				}

				for (auto ship = ships.begin(); ship != ships.end(); ++ship) {
					isShipHit = ship->checkIfHit(playerCoordinates);
					cout << ship->getShipStatus() << endl;
					if (isShipHit) {
						cout << "Hit!" << endl;
						board[playerCoordinates[0] - 1][playerCoordinates[1] - 1] = 'X';
						playerScore += (5 * scoreMultiplier);
						break;
					}
				}

				if (!isShipHit) {
					cout << "Miss!" << endl;
					board[playerCoordinates[0] - 1][playerCoordinates[1] - 1] = 'O';
				}

				cin >> userInput;

				turnsLeft -= 1;
			}

			if (turnsLeft == 0) {
				gameOver = true;
				clearScreen();
				cout << "Game Over!" << endl;
			}
			else if (ships.size() == 0) {
				gameOver = true;
				clearScreen();
				cout << "Victory!" << endl;
			}
		}

		userConfirm = false;
		while (!userConfirm) {
			cout << "Would you like to play again? (Y/N): ";
			cin >> userInput;

			if (userInput == "Y" || userInput == "y") {
				gameOver = false;
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
