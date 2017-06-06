/*
 * TicTacToeTable.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: yanzh
 */

#include "AnimationEquation.h"
#include "Displayable.h"
#include "Clickable.h"
#include "TicTacToeTable.h"

#include "ImgCrosses.h"
#include "ImgNought.h"
#include "Rect.h"

#include <SDL.h>

#include <chrono>

namespace GUI
{
namespace TTT
{

int TicTacToeTable::_grid_width = 20;

std::chrono::duration<int, std::nano> TicTacToeTableGrid::_duration_of_animation =
		std::chrono::milliseconds(800);

TicTacToeTable::TicTacToeTable(SDL_Renderer *renderer, TicTacToe *tictactoe) :
		Displayable(renderer), _tictactoe(tictactoe)
{
	int i, j;

	_w = 256 * 3 + _grid_width * 2;
	_h = 256 * 3 + _grid_width * 2;

	_imgCrosses = new ImgCrosses**[3];
	_imgNought = new ImgNought**[3];
	for (i = 0; i < 3; ++i)
	{
		_imgCrosses[i] = new ImgCrosses*[3];
		_imgNought[i] = new ImgNought*[3];
		for (j = 0; j < 3; ++j)
		{
			_imgCrosses[i][j] = new ImgCrosses(_renderer);
			_imgNought[i][j] = new ImgNought(_renderer);
			_imgCrosses[i][j]->setVisible(false);
			_imgNought[i][j]->setVisible(false);
		}
	}

	_grid_v = new TicTacToeTableGrid*[2];
	_grid_h = new TicTacToeTableGrid*[2];
	for (i = 0; i < 2; ++i)
	{
		_grid_v[i] = new TicTacToeTableGrid(_renderer);
		_grid_h[i] = new TicTacToeTableGrid(_renderer);
		_grid_v[i]->setWidthNLength(20, _h);
		_grid_h[i]->setWidthNLength(_w, 20);
		_grid_v[i]->setPosition(_x + (i + 1) * 256 + i * _grid_width, _y);
		_grid_h[i]->setPosition(_x, _y + (i + 1) * 256 + i * _grid_width);
		_grid_v[i]->setColor(
		{ 13, 161, 146, 255 });
		_grid_h[i]->setColor(
		{ 13, 161, 146, 255 });
	}
}

TicTacToeTable::~TicTacToeTable()
{
	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			delete _imgCrosses[i][j];
			delete _imgNought[i][j];
		}
		delete _imgCrosses[i];
		delete _imgNought[i];
	}
	delete _imgCrosses;
	delete _imgNought;

	for (i = 0; i < 2; ++i)
	{
		delete _grid_v[i];
		delete _grid_h[i];
	}
	delete _grid_v;
	delete _grid_h;
}

void TicTacToeTable::show(const Table &table)
{
	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			if (table[i][j] == Piece::CROSSES)
			{
				_imgCrosses[i][j]->show();
				_imgNought[i][j]->hide();
			}
			else if (table[i][j] == Piece::NOUGHT)
			{
				_imgNought[i][j]->show();
				_imgCrosses[i][j]->hide();
			}
			else
			{
				_imgCrosses[i][j]->hide();
				_imgNought[i][j]->hide();
			}
		}
	}
}

void TicTacToeTable::reSet(const Table &table)
{
	for (int i = 0; i < 2; ++i)
	{
		_grid_v[i]->show();
		_grid_h[i]->show();
	}
	show(table);
}

void TicTacToeTable::setPosition(int x, int y)
{
	int i, j;
	int imgx, imgy;
	_x = x;
	_y = y;
	Clickable::_x = _x;
	Clickable::_y = _y;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			imgx = _x + j * 256 + j * _grid_width;
			imgy = _y + i * 256 + i * _grid_width;
			_imgCrosses[i][j]->setPosition(imgx, imgy);
			_imgNought[i][j]->setPosition(imgx, imgy);
		}
	}
	for (i = 0; i < 2; ++i)
	{
		_grid_v[i]->setPosition(_x + (i + 1) * 256 + i * _grid_width, _y);
		_grid_h[i]->setPosition(_x, _y + (i + 1) * 256 + i * _grid_width);
	}
}

void TicTacToeTable::display()
{
	int i, j;
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			_imgCrosses[i][j]->display();
			_imgNought[i][j]->display();
		}
	}
	for (i = 0; i < 2; ++i)
	{
		_grid_v[i]->display();
		_grid_h[i]->display();
	}
}

void TicTacToeTable::onClick(const SDL_Event &event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int x = event.motion.x;
		int y = event.motion.y;
		int col = (x - _x) / (256 + _grid_width);
		int row = (y - _y) / (256 + _grid_width);
		if (col >= 0 && col <= 2 && row >= 0 && row <= 2)
		{
			if (_tictactoe->winner() == Piece::NONE)
			{
				if (_tictactoe->getTable()[row][col] == Piece::NONE)
				{
					Player *player = nullptr;
					if ((player = _tictactoe->nextPlayer()) != nullptr
							&& !player->isAI())
					{
						_tictactoe->set(row, col, *player);
						_tictactoe->nextMove();
						show(_tictactoe->getTable());
					}
				}
			}
		}
	}
}

void TicTacToeTable::onTop(const SDL_Event &evnet)
{
}

TicTacToeTableGrid::TicTacToeTableGrid(SDL_Renderer *renderer) :
		Rect(renderer)
{
	_animation_start_time = std::chrono::system_clock::now();
}

TicTacToeTableGrid::~TicTacToeTableGrid()
{
}

void TicTacToeTableGrid::display()
{
	if (_is_display)
	{
		if (!_is_animation_finished)
		{
			std::chrono::time_point<std::chrono::system_clock> now =
					std::chrono::system_clock::now();
			if (now - _animation_start_time < _duration_of_animation)
			{
				if (_w > _h)
				{
					_rect.y = _y;
					_rect.h = _h;
					_rect.w = squareRootAnimate(
							(int) (now - _animation_start_time).count(), 0,
							(int) _duration_of_animation.count(), 0, _w);
					_rect.x = _x + _w / 2 - _rect.w / 2;
				}
				else
				{
					_rect.x = _x;
					_rect.w = _w;
					_rect.h = squareRootAnimate(
							(int) (now - _animation_start_time).count(), 0,
							(int) _duration_of_animation.count(), 0, _h);
					_rect.y = _y + _h / 2 - _rect.h / 2;
				}
			}
			else
			{
				_rect.x = _x;
				_rect.y = _y;
				_rect.w = _w;
				_rect.h = _h;
				_is_animation_finished = true;
			}
		}
		Displayable::display();
	}
}

void TicTacToeTableGrid::setPosition(int x, int y)
{
	_x = x;
	_y = y;
	_rect.x = _x;
	_rect.y = _y;
	show();
}

void TicTacToeTableGrid::setWidthNLength(int w, int h)
{
	_w = w;
	_h = h;
	_rect.w = _w;
	_rect.h = _h;
}

void TicTacToeTableGrid::show()
{
	_animation_start_time = std::chrono::system_clock::now();
	_is_animation_finished = false;
}

void TicTacToeTableGrid::hide()
{
	_is_display = false;
}

} /* namespace TTT */
} /* namespace GUI */
