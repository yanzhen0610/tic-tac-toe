/*
 * TicTacToeWindow.cpp
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#include "TicTacToeWindow.h"
#include "ImgCrosses.h"
#include "ImgNought.h"
#include "Player.h"
#include "Piece.h"

#include "Table.h"
#include "TicTacToe.h"
#include "Player.h"
#include "Piece.h"
#include "TTTException.h"

#include <SDL.h>

#include <iostream>
#include <functional>

namespace GUI
{
namespace TTT
{

int TicTacToeWindow::_base_table_x = 400;
int TicTacToeWindow::_base_table_y = 50;

static void action_undo(TicTacToe &t, TicTacToeTable &table);

TicTacToeWindow::TicTacToeWindow() :
		Window("Tic Tac Toe", 1600, 900), _tictactoe(), _ai(), _p(), _table(
				getRenderer(), &_tictactoe), _button_undo(_renderer), _button_restart(
				_renderer)
{
	_p.setPiece(Piece::CROSSES);
	_ai.setPiece(Piece::NOUGHT);

	_tictactoe.setPlayer1(_p);
	_tictactoe.setPlayer2(_ai);

//	_table.setClickAreaX(_base_table_x);
//	_table.setClickAreaY(_base_table_y);
	_table.setPosition(_base_table_x, _base_table_y);
	addDisplayable(&_table);
	addClickable(&_table);

	_button_undo.setPosition(1300, 100);
	_button_undo.setButtonText("undo");
	_button_undo.setButtonTextColor(
	{ 20, 189, 172, 255 });
	_button_undo.setButtonTextFontSize(80);
	_button_undo.setButtonBackgroundColor(
	{ 13, 161, 146, 255 });
	_button_undo.addButtonAction(1,
			std::bind(action_undo, std::ref(_tictactoe), std::ref(_table)));
	addClickable(&_button_undo);
	addDisplayable(&_button_undo);

	_button_restart.setPosition(1300, 700);
	_button_restart.setButtonText("restart");
	_button_restart.setButtonTextColor(
	{ 20, 189, 172, 255 });
	_button_restart.setButtonTextFontSize(80);
	_button_restart.setButtonBackgroundColor(
	{ 13, 161, 146, 255 });
	_button_restart.addButtonAction(1,
			std::bind(&TicTacToe::restartGame, &_tictactoe));
	_button_restart.addButtonAction(1,
			std::bind(&TicTacToeTable::reSet, &_table,
					std::bind(&TicTacToe::getTable, &_tictactoe)));
	addClickable(&_button_restart);
	addDisplayable(&_button_restart);
}

TicTacToeWindow::~TicTacToeWindow()
{
	// TODO Auto-generated destructor stub
}

static void action_undo(TicTacToe &t, TicTacToeTable &table)
{
	Player* player = t.lastPlayer();
	if (player != nullptr)
	{
		if (player->isAI())
		{
			t.undo();
		}
		t.undo();
		table.show(t.getTable());
	}
}

} /* namespace TTT */
} /* namespace GUI */
