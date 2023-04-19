#include "Console.h"
#include "TicTacToeConsoleApp.h"
#include <iostream>
int main()
{
	int playersAmount;
	Console::clear();
	std::cout << "Mode:\n"
			  << "0 - two CPU players\n"
			  << "1 - play with CPU\n"
			  << "2 - two players\n";
	Console::getInputUntilSuccess(playersAmount);
	if (playersAmount < 0 || playersAmount > 2) {
		return EXIT_SUCCESS;
	}
	TicTacToeConsoleApp::intro();
	do {
		TicTacToeConsoleApp game(playersAmount);
		game.printBoard();
		while (game.isRunning()) {
			game.step();
		};
		int continuation;
		std::cout << "Play again?\n"
				  << "1 - yes\n"
				  << "0 - no\n";
		Console::getInputUntilSuccess(continuation);

		if (continuation == 0) {
			break;
		}
	} while (true);
}