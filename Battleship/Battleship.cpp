// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 12/8/19

#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

class Ship {
	int shipXCoordinate = generateShipX(), shipYCoordinate = generateShipY();
	bool isShipHorizontal = generateShipOrientation();

public:
	int generateShipX() {
		int x = rand() % 4 + 0;

		return x;
	}

	int generateShipY() {
		int y = rand() % 4 + 0;

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
};

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

void printBoard(char board[10][10]) {
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
		if (i != 9) {
			cout << endl << "|---+---+---+---+---+---+---+---+---+---|" << endl;
		}
	}
	cout << endl << "-----------------------------------------" << endl << "  1   2   3   4   5   6   7   8   9  10" << endl;
}

int main()
{
	string userInput;
	bool isRunning = true;
	//int shipXCoordinate, shipYCoordinate;
	//bool isShipHorizontal;

	while (isRunning) {

		bool userConfirm = false, gameOver = false;
		char board[10][10] = {
			{' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' '},
			{' ', ' ', ' ', ' ', ' '},
		};

		//shipXCoordinate = generateShipX();
		//shipYCoordinate = generateShipY();

		Ship ship();

		//board[ship]

		while (!gameOver) {
			clearScreen();

			printBoard(board);

			cout << "Press any button to continue." << endl;
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
