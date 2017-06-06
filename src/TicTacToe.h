#ifndef _TIC_TAC_TOE_H_
#define _TIC_TAC_TOE_H_

#include "Movement.h"
#include "Player.h"
#include "Table.h"
#include "TTTException.h"

#include <Vector>
#include <map>

namespace TTT
{
	class TicTacToe
	{
	public:
	    TicTacToe();
	    TicTacToe(const TicTacToe &other);
	    virtual ~TicTacToe();

	    bool set(int row, int col, const Player &player);
	    bool undo();
	    void nextMove();
	    Piece winner() const;
	    Player* nextPlayer() const;
	    Player* lastPlayer() const;
	    void restartGame();

	    inline void setPlayer1(Player &player) {
	        this->player1 = &player;
	        player1_ID = player.getID();
        };
	    inline void setPlayer2(Player &player) {
	        this->player2 = &player;
	        player2_ID = player.getID();
        };
	    inline Player* getPlayer1() { return player1; };
	    inline Player* getPlayer2() { return player2; };
	    inline Piece getPiece(int row, int col) { return this->table[row][col]; };
	    inline const Table getTable() { return Table(table); };
	    inline const int getWin(const Piece piece) const { return win.at(piece); }
	private:
		bool checkPlayer() const;

	private:
	    std::vector<Movement> movements;
	    int player1_ID;
	    int player2_ID;
	    std::map<Piece, int> win;
	    Player *player1 = nullptr;
	    Player *player2 = nullptr;
	    Table table;

	    const static int DEFAULT_P_ID;
	};
}

#endif
