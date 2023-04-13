#include "TicTacToe.h"
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>
TicTacToe::TicTacToe()
{
	m_players.push_back(std::make_unique<PlayerHuman>());
	m_players.push_back(std::make_unique<PlayerCPU>());
	initGame();
}
TicTacToe::TicTacToe(const int numberOfHumanPlayers)
{
	switch (numberOfHumanPlayers) {
	case 0:
		m_players.push_back(std::make_unique<PlayerCPU>("CPU 1"));
		m_players.push_back(std::make_unique<PlayerCPU>("CPU 2"));
		break;
	case 1:
		m_players.push_back(std::make_unique<PlayerHuman>("Player"));
		m_players.push_back(std::make_unique<PlayerCPU>("CPU"));
		break;
	case 2:
	default:
		m_players.push_back(std::make_unique<PlayerHuman>("Player 1"));
		m_players.push_back(std::make_unique<PlayerHuman>("Player 2"));
	}
	initGame();
}
void TicTacToe::initGame()
{
	initializeAllowed();
	initializeBoard();
}
void TicTacToe::step()
{
	std::cout << "Player: " << m_players[m_currentPlayer]->getName() << std::endl;
	int selectedField;
	while (true) {
		selectedField = m_players[m_currentPlayer]->ProvideField(m_allowed);
		if (isMoveAllowed(selectedField)) {
			break;
		}
	}
	takeFieldOnBoard(selectedField, returnPlayerSign(m_currentPlayer));
	clearConsole();
	printBoard();
	if (isGameWon()) {
		std::cout << std::endl
				  << m_players[m_currentPlayer]->getName() << " - " << returnPlayerSign(m_currentPlayer) << " won!" << std::endl;
		terminate();
		return;
	}
	if (!areThereFreeFields()) {
		std::cout << "Game ended" << std::endl;
		terminate();
		return;
	}
	nextPlayer();
}
void TicTacToe::takeFieldOnBoard(const int field, const char sign)
{
	m_allowed[field] = false;
	m_board[field] = sign;
}
char TicTacToe::returnPlayerSign(const PlayerID player)
{
	if (player == 0) {
		return 'x';
	}
	return 'o';
}
void TicTacToe::nextPlayer()
{
	m_currentPlayer += 1;
	m_currentPlayer %= 2;
}
void TicTacToe::clearConsole()
{
	system("clear");
}
void TicTacToe::printBoard()
{
	for (int i = 0; i < 9; i += 3) {
		std::cout << m_board[i] << '|' << m_board[i + 1] << '|' << m_board[i + 2] << std::endl;
		if (i < 6) {
			std::cout << "_____" << std::endl;
		}
	}
}
void TicTacToe::intro()
{
	std::cout << "Tic Tac Toe game" << std::endl;
	std::cout << "To make a move, enter number of field" << std::endl;
}
std::string TicTacToe::getInputFromConsole()
{
	std::string input;
	std::cin >> input;
	return input;
}
bool TicTacToe::isRunning()
{
	return m_running;
}
void TicTacToe::terminate()
{
	m_running = false;
}
void TicTacToe::initializeAllowed()
{
	for (int i = 0; i < 9; i++) {
		m_allowed[i] = true;
	};
}
void TicTacToe::initializeBoard()
{
	for (int i = 0; i < 9; i++) {
		m_board[i] = i + '0';
	};
}
bool TicTacToe::isMoveAllowed(const int field)
{
	if (field >= 0 && field < 9) {
		return m_allowed[field];
	}
	return false;
}
bool TicTacToe::isGameWon()
{
	if (checkAllCols()) {
		return true;
	}
	if (checkAllRows()) {
		return true;
	}
	if (checkDiagonals()) {
		return true;
	}
	return false;
}
bool TicTacToe::checkRow(const int row)
{
	if (m_board[row] == m_board[row + 1] && m_board[row + 1] == m_board[row + 2]) {
		return true;
	}
	return false;
}
bool TicTacToe::checkAllRows()
{
	for (int i = 0; i < 9; i += 3) {
		if (checkRow(i)) {
			return true;
		}
	}
	return false;
}
bool TicTacToe::checkCol(const int col)
{
	if (m_board[col] == m_board[col + 3] && m_board[col + 3] == m_board[col + 6]) {
		return true;
	}
	return false;
}
bool TicTacToe::checkAllCols()
{
	for (int i = 0; i < 3; i++) {
		if (checkCol(i)) {
			return true;
		}
	}
	return false;
}
bool TicTacToe::checkDiagonals()
{
	if (m_board[0] == m_board[4] && m_board[4] == m_board[8]) {
		return true;
	}
	if (m_board[2] == m_board[4] && m_board[4] == m_board[6]) {
		return true;
	}
	return false;
}
bool TicTacToe::areThereFreeFields()
{
	for (int i = 0; i < 9; i++) {
		if (m_allowed[i])
			return true;
	}
	return false;
}