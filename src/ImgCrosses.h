/*
 * ImgCrosses.h
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#ifndef SRC_IMGCROSSES_H_
#define SRC_IMGCROSSES_H_

#include "ImgPiece.h"

namespace GUI
{
namespace TTT
{

class ImgCrosses: public ImgPiece
{
public:
	ImgCrosses(SDL_Renderer *renderer);
	virtual ~ImgCrosses();
};

} /* namespace TTT */
} /* namespace GUI */

#endif /* SRC_IMGCROSSES_H_ */
