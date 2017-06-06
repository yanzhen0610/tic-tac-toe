#include "Player.h"

#include <iostream>
using namespace std;

using namespace TTT;

int Player::creationCount = 0;

LocalPlayer::LocalPlayer() :
		Player()
{
}

LocalPlayer::LocalPlayer(const LocalPlayer &other) :
		Player(other)
{
}

LocalPlayer::~LocalPlayer()
{
}

const Movement LocalPlayer::nextStep(const Table &talbe) const
{
	return Movement();
}

AI_Impossible::AI_Impossible() :
		Player()
{
}

AI_Impossible::AI_Impossible(const AI_Impossible &other) :
		Player(other)
{
}

AI_Impossible::~AI_Impossible()
{
}

static Piece winner(const Table &table)
{
	static const int TL = Table::TABLE_L;
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
		if (p1 != Piece::NONE)
			if (c1 == TL)
				return p1;
		if (p2 != Piece::NONE)
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
		if (p1 != Piece::NONE)
			if (c1 == TL)
				return p1;
		if (p2 != Piece::NONE)
			if (c2 == TL)
				return p2;
	}

	return TTT::NONE;
}

inline static Piece hostile(Piece piece)
{
	if (piece == Piece::CROSSES)
		return Piece::NOUGHT;
	if (piece == Piece::NOUGHT)
		return Piece::CROSSES;
	return Piece::NONE;
}

static int minimax(const Table &table, Piece piece)
{
	const int TL = Table::TABLE_L;
	Piece winnerPiece = winner(table);
	if (winnerPiece == piece)
	{
		return 1;
	}
	else if (winnerPiece == hostile(piece))
	{
		return -1;
	}

	int score = -2, thisScore;
	int i, j;
	for (i = 0; i < TL; ++i)
	{
		for (j = 0; j < TL; ++j)
		{
			if (table[i][j] == Piece::NONE)
			{
				Table _table(table);
				_table[i][j] = piece;
				thisScore = -minimax(_table, hostile(piece));
				if (thisScore > score)
				{
					score = thisScore;
				}
			}
		}
	}
	if (score == -2)
	{
		return 0;
	}
	return score;
}

const Movement AI_Impossible::nextStep(const Table &table) const
{
	auto TL = Table::TABLE_L;
	Piece piece = getPiece();
	int movei, movej;
	int score = -2, tempScore;
	int i, j;
	for (i = 0; i < TL; ++i)
	{
		for (j = 0; j < TL; ++j)
		{
			if (table[i][j] == Piece::NONE)
			{
				Table _table(table);
				_table[i][j] = piece;
				tempScore = -minimax(_table, hostile(piece));
				if (tempScore > score)
				{
					score = tempScore;
					movei = i;
					movej = j;
				}
			}
		}
	}
	if (score == -2)
	{
		return Movement();
	}
	return Movement(movei, movej, piece, getID());
}
