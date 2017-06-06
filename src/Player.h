#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Movement.h"
#include "Piece.h"
#include "Table.h"
#include "TTTException.h"

#include <string>

using std::string;

namespace TTT
{
	class Player
	{
	public:
		inline Player() :
		    playerID(creationCount++), name(""), piece(TTT::NONE) {};
		inline Player(const string &name, Piece piece) :
		    playerID(creationCount++), name(name), piece(piece) {};
		inline Player(const Player &other) :
		    playerID(other.playerID), name(other.name), piece(other.piece) {};
		inline virtual ~Player() {};

		virtual const Movement nextStep(const Table &table) const = 0;
		virtual bool isAI() const = 0;

		inline void setPiece(Piece piece) { this->piece = piece; }
		inline void setName(string name) { this->name = name; }
		inline Piece getPiece() const { return this->piece; }
		inline string getName() const { return this->name; }
		inline int getID() const { return this->playerID; }
		inline bool operator =(const Player &other) {
			if (this->playerID == other.playerID)
				return true;
			return false;
		}

	private:
		static int creationCount;
		const int playerID;
		string name;
		Piece piece;
	};

	// a human player
	class LocalPlayer : public Player
	{
	public:
		LocalPlayer();
		LocalPlayer(const LocalPlayer &other);
		virtual ~LocalPlayer();

		inline virtual bool isAI() const { return false; }
		virtual const Movement nextStep(const Table &table) const;

	private:
	};

	// an AI player that's impossible to be defeated
	class AI_Impossible : public Player
	{
	public:
		AI_Impossible();
		AI_Impossible(const AI_Impossible &other);
		virtual ~AI_Impossible();

		inline virtual bool isAI() const { return true; }
		virtual const Movement nextStep(const Table &table) const;

	private:
	};
}

#endif
