/*
 * main.cpp
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#include "TicTacToeWindow.h"

#include <iostream>

void startTicTacToe();

int main(int argc, char **argv)
{
	startTicTacToe();
	std::cout << "ended\n";
	return 0;
}

void startTicTacToe()
{
	GUI::TTT::TicTacToeWindow tttw;
#ifdef __DEBUG__
	tttw.showFPS(true);
#endif // __DEBUG__
	tttw.start();
	std::cout << "Thread " << std::this_thread::get_id() << " start handling\n";
	GUI::EventHandler::startHandling();
	std::cout << "Thread " << std::this_thread::get_id() << " end handling\n";
	std::cout << "Thread " << std::this_thread::get_id() << " startMain ended\n";
}
