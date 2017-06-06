/*
 * TicTacToeTable.h
 *
 *  Created on: Jun 4, 2017
 *      Author: yanzh
 */

#ifndef SRC_TICTACTOETABLE_H_
#define SRC_TICTACTOETABLE_H_

#include "Clickable.h"
#include "Displayable.h"
#include "Rect.h"

#include "ImgCrosses.h"
#include "ImgNought.h"

#include "Piece.h"
#include "Table.h"
#include "TicTacToe.h"
#include "Player.h"

#include <SDL.h>

#include <chrono>

using TTT::Piece;
using TTT::Table;
using TTT::TicTacToe;
using TTT::Player;
using TTT::AI_Impossible;
using TTT::LocalPlayer;

namespace GUI
{
namespace TTT
{

class TicTacToeTableGrid;

class TicTacToeTable: public Displayable, public Clickable
{
public:
	TicTacToeTable(SDL_Renderer *renderer, TicTacToe *tictactoe);
	virtual ~TicTacToeTable();

	void show(const Table &table);
	void reSet(const Table &table);

	virtual void setPosition(int x, int y);

	virtual void display();

	virtual void onClick(const SDL_Event &event);
	virtual void onTop(const SDL_Event &event);

private:
	std::chrono::time_point<std::chrono::system_clock> _added_time = std::chrono::system_clock::now();
	TicTacToe *_tictactoe = nullptr;
	ImgCrosses ***_imgCrosses = nullptr;
	ImgNought ***_imgNought = nullptr;
	TicTacToeTableGrid **_grid_v = nullptr;
	TicTacToeTableGrid **_grid_h = nullptr;
	int _x = 0;
	int _y = 0;

private:
	static int _grid_width;
};

class TicTacToeTableGrid: public Rect
{
public:
	TicTacToeTableGrid(SDL_Renderer *renderer);
	virtual ~TicTacToeTableGrid();

	virtual void display();

	virtual void setPosition(int x, int y);
	virtual void setWidthNLength(int w, int h);

	void show();
	void hide();

private:
	int _x = 0;
	int _y = 0;
	int _w = 10;
	int _h = 10;

	std::chrono::time_point<std::chrono::system_clock> _animation_start_time;
	bool _is_animation_finished = false;

private:
	static std::chrono::duration<int, std::nano> _duration_of_animation;
};

} /* namespace TTT */
} /* namespace GUI */

#endif /* SRC_TICTACTOETABLE_H_ */
