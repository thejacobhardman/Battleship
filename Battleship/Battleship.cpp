// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 12/8/19

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void printBoard(char board[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

int main()
{
	string userInput;
	bool isRunning = true,  userConfirm = false, gameOver = false;
	char board[5][5] = {
		{' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' '},
	};

	while (isRunning) {

		while (!gameOver) {
			printBoard(board);
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
