#ifndef _TTT_Exception_H_
#define _TTT_Exception_H_

#include "Piece.h"

#include <string>

namespace TTT
{
    class TTTException
    {
    public:
        enum TYPE
        {
            UNDIFINED = 0x0,
            NO_PLAYER1 = 0x10,
            NO_PLAYER2 = 0x11,
            PLAYER1_WIN = 0x12,
            PLAYER2_WIN = 0x13,
            NEXT_PLAYER_NOT_FOUND = 0x14,
            DRAW = 0x100,
            NO_MORE_MOVEMENT = 0x101,
            WINNER_EXIST_OR_DRAW = 0x102
        };
        inline TTTException(const TYPE type) : type(type) { };
        inline TTTException(const std::string &msg) :
            type(UNDIFINED), message(msg) { };
        inline TTTException(const TYPE type, std::string msg) :
            type(type), message(msg) { };
        inline TTTException(const TTTException &other) :
            TTTException(other.type, other.message) { };
        inline virtual ~TTTException() { };

        const TYPE type;
        const std::string message;
    };
}

#endif
