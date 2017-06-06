#include "Table.h"

using namespace TTT;

const int Table::TABLE_L = 3;

Table::Table()
{
    int i, j;
    table = new Piece*[TABLE_L];
    for (i = 0; i < TABLE_L; ++i)
        table[i] = new Piece[TABLE_L];
    for (i = 0; i < TABLE_L; ++i)
        for (j = 0; j < TABLE_L; ++j)
            table[i][j] = TTT::NONE;
}

Table::Table(const Table &other) : Table()
{
    int i, j;
    for (i = 0; i < TABLE_L; ++i)
        for (j = 0; j < TABLE_L; ++j)
            table[i][j] = other[i][j];
}

Table::~Table()
{
    for (int i = 0; i < TABLE_L; ++i)
        delete[] table[i];
    delete table;
}
