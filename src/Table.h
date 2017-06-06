#ifndef _TABLE_H_
#define _TABLE_H_

#include "Piece.h"

namespace TTT
{
	struct Table
	{
	public:
		const static int TABLE_L;
		Piece **table;
	public:
		Table();
		Table(const Table& other);
		virtual ~Table();

		inline Piece* operator[](int index) const {
		    return (Piece*)table[index];
		};

		inline Table& operator=(const Table &other) {
		    int i, j;
		    for (i = 0; i < TABLE_L; i++)
                for (j = 0; j < TABLE_L; j++)
                    (*this)[i][j] = other[i][j];
            return *this;
		};
	};
}

#endif
