/*
 * ImgNought.h
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#ifndef SRC_IMGNOUGHT_H_
#define SRC_IMGNOUGHT_H_

#include "ImgPiece.h"

#include <SDL.h>

namespace GUI
{
namespace TTT
{

class ImgNought: public ImgPiece
{
public:
	ImgNought(SDL_Renderer *renderer);
	virtual ~ImgNought();
};

} /* namespace TTT */
} /* namespace GUI */

#endif /* SRC_IMGNOUGHT_H_ */
