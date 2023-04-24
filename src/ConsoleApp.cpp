#include "ConsoleApp.h"
#include <iostream>
void ConsoleApp::onBeforeStep() const
{
	const auto& currentPlayer = m_players[currentPlayerId()].get();
	std::cout << "Player: " << currentPlayer->getName() << '\n';
}
void ConsoleApp::onInvalidMove() const
{
	std::cout << "Invalid move\n";
}
void ConsoleApp::onWin(Player* currentPlayer) const
{
	std::cout
		<< currentPlayer->getName() << "(" << currentPlayer->getSign() << ") won!\n";
}
void ConsoleApp::onDraw() const
{
	std::cout << "Draw!\n";
}
void ConsoleApp::onInput() const
{
	std::cout << "Field #";
}
void ConsoleApp::printBoard() const
{
	std::cout << '\n';
	for (int i = 0; i < 9; i += 3) {
		std::cout << m_board.getBoardArray()[i] << '|' << m_board.getBoardArray()[i + 1] << '|' << m_board.getBoardArray()[i + 2] << '\n';
		if (i < 6) {
			std::cout << "_____\n";
		}
	}
	std::cout << '\n';
}
void ConsoleApp::intro()
{
	std::cout << "Tic Tac Toe game\n"
			  << "To make a move, enter number field id when asked\n"
			  << "Mode:\n"
			  << "0 - two CPU players\n"
			  << "1 - play with CPU\n"
			  << "2 - two players\n";
}