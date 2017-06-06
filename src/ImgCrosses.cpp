/*
 * ImgCrosses.cpp
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#include "ImgCrosses.h"
#include "Image.h"

namespace GUI
{
namespace TTT
{

ImgCrosses::ImgCrosses(SDL_Renderer *renderer) : ImgPiece(renderer, "res/pic/crosses.png")
{
}

ImgCrosses::~ImgCrosses()
{
	// TODO Auto-generated destructor stub
}

} /* namespace TTT */
} /* namespace GUI */
