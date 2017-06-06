#include "TicTacToe.h"

#include <iostream>

using namespace std;

using namespace TTT;

const int TicTacToe::DEFAULT_P_ID = -1;

TicTacToe::TicTacToe() :
		player1_ID(DEFAULT_P_ID), player2_ID(DEFAULT_P_ID), player1(NULL), player2(
		NULL)
{
}

TicTacToe::TicTacToe(const TicTacToe &other) :
		movements(other.movements), player1_ID(other.player1_ID), player2_ID(
				other.player2_ID), player1(other.player1), player2(
				other.player2), table(other.table)
{
}

TicTacToe::~TicTacToe()
{
}

bool TicTacToe::set(int row, int col, const Player &player)
{
	if (row >= 0 && row < Table::TABLE_L && col >= 0 && col < Table::TABLE_L)
	{
		if (movements.size() < 9)
		{
			Piece piece = player.getPiece();
			int movs = movements.size();
			Movement m(row, col, piece, player.getID());
//			Piece piece;

			for (int i = 0; i < movs; i++)
			{
				if (movements.at(i) == m)
				{
					return false;
				}
			}
			if (table[row][col] != TTT::NONE)
			{
				return false;
			}
			movements.push_back(m);
			table[row][col] = piece;
			if ((piece = winner()) != Piece::NONE)
			{
				++win[piece];
			}
			return true;
		}
	}
	return false;
}

bool TicTacToe::undo()
{
	if (movements.size())
	{
		Movement m = movements.back();
		table[m.row][m.col] = TTT::NONE;
		movements.erase(movements.end());
		return true;
	}
	return false;
}

Player* TicTacToe::lastPlayer() const
{
	if (movements.size())
	{
		Movement m = movements.back();
		if (m.playerID == player1_ID)
		{
			return player1;
		}
		else if (m.playerID == player2_ID)
		{
			return player2;
		}
	}
	return player1;
}

Player* TicTacToe::nextPlayer() const
{
	if (checkPlayer())
	{
		if (movements.size())
		{
			Movement m = movements.back();
			if (winner() == TTT::NONE)
			{
				if (m.playerID == player1_ID)
				{
					return player2;
				}
				else if (m.playerID == player2_ID)
				{
					return player1;
				}
				else
				{
					return nullptr;
				}
			}
		}
		return player1;
	}
	return nullptr;
}

void TicTacToe::nextMove()
{
	if (checkPlayer())
	{
		Movement newMovement;
		Player *player = nullptr;

		if (movements.size())
		{
			if (movements.size()
					< (unsigned int) (Table::TABLE_L * Table::TABLE_L))
			{
				if ((player = nextPlayer()) != nullptr)
				{
					newMovement = player->nextStep(getTable());
					set(newMovement.row, newMovement.col, *player);
				}
			}
		}
		else
		{
			if ((player = player1)->isAI())
			{
				newMovement = Movement(player->nextStep(getTable()));
			}
			set(newMovement.row, newMovement.col, *player);
		}
	}
}

Piece TicTacToe::winner() const
{
	const int TL = Table::TABLE_L;
	int i, j, c1, c2;
	Piece p1, p2;

	// horizontally and vertically check
	for (i = 0; i < TL; ++i)
	{
		c1 = 0, c2 = 0;
		p1 = table[i][0];
		p2 = table[0][i];
		for (j = 0; j < TL; ++j)
		{
			if (p1 == table[i][j])
				++c1;
			if (p2 == table[j][i])
				++c2;
		}
		if (c1 == TL)
			return p1;
		if (c2 == TL)
			return p2;
	}

	// diagonally check
	{
		p1 = table[0][0];
		p2 = table[0][TL - 1];
		c1 = 0, c2 = 0;
		for (i = 0; i < TL; ++i)
		{
			j = TL - i - 1;
			if (p1 == table[i][i])
				++c1;
			if (p2 == table[i][j])
				++c2;
		}
		if (c1 == TL)
			return p1;
		if (c2 == TL)
			return p2;
	}

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			if (table[i][j] == Piece::NONE)
			{
				return Piece::NONE;
			}
		}
	}

	return Piece::DRAW;
}

bool TicTacToe::checkPlayer() const
{
	if (player1_ID == DEFAULT_P_ID || player1 == NULL)
	{
		return false;
	}
	if (player2_ID == DEFAULT_P_ID || player2 == NULL)
	{
		return false;
	}
	return true;
}

void TicTacToe::restartGame()
{
	movements.clear();
	table = Table();
}
