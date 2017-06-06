#ifndef _Movement_H_
#define _Movement_H_

#include "Piece.h"

namespace TTT
{
struct Movement
{
	inline Movement() : isAllowReplace(true) { };
	inline Movement(int row, int col, Piece piece, const int playerID) :
			row(row), col(col), piece(piece), playerID(playerID) { };
	inline Movement(const Movement &other) :
			row(other.row), col(other.col), piece(other.piece), playerID(
					other.playerID) { };

//        inline int getRow() { return row; };
//        inline int getCol() { return col; };
//        inline Piece getPiece() { return piece; };
//        inline int getPlayerID() { return playerID; };

	const bool isAllowReplace = false;
	const int row = -1;
	const int col = -1;
	const Piece piece = Piece::DRAW;
	const int playerID = -1;

	inline Movement& operator =(const Movement &other)
	{
		if (isAllowReplace)
		{
			*(int*)&row = other.row;
			*(int*)&col = other.col;
			*(Piece*)&piece = other.piece;
			*(int*)&playerID = other.playerID;
		}
		return *this;
	}

	inline bool operator ==(const Movement &other) const
	{
		if (this->row == other.row && this->col == other.col
				&& this->piece == other.piece)
		{
			return true;
		}
		return false;
	}
};
}

#endif
