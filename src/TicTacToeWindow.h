/*
 * TicTacToeWindow.h
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#ifndef SRC_TICTACTOEWINDOW_H_
#define SRC_TICTACTOEWINDOW_H_

#include "Window.h"
#include "Button.h"
#include "ImgCrosses.h"
#include "ImgNought.h"
#include "TicTacToeTable.h"

#include "Table.h"
#include "TicTacToe.h"
#include "Player.h"
#include "Piece.h"
#include "TTTException.h"

#include <vector>

using TTT::Table;
using TTT::Piece;
using TTT::TicTacToe;
using TTT::Player;
using TTT::LocalPlayer;
using TTT::AI_Impossible;
using TTT::TTTException;

namespace GUI
{
namespace TTT
{

class TicTacToeWindow: public Window
{
public:
	TicTacToeWindow();
	virtual ~TicTacToeWindow();

private:
	std::vector<ImgCrosses*> _crosses;
	std::vector<ImgNought*> _nought;

	TicTacToe _tictactoe;
	Player *_player1 = nullptr;
	Player *_player2 = nullptr;

	AI_Impossible _ai;
	LocalPlayer _p;

	TicTacToeTable _table;

	Button _button_undo;
	Button _button_restart;

private:
	static int _base_table_x;
	static int _base_table_y;
};

} /* namespace TTT */
} /* namespace GUI */

#endif /* SRC_TICTACTOEWINDOW_H_ */
