/*
 * Rect.h
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#ifndef SRC_RECT_H_
#define SRC_RECT_H_

#include "Displayable.h"

#include <SDL.h>

namespace GUI
{

class Rect: public Displayable
{
public:
	Rect(SDL_Renderer *renderer);
	Rect(SDL_Renderer *renderer, const SDL_Color &color, int w, int h);
	virtual ~Rect();

	virtual void createSurface();
	virtual void setColor(const SDL_Color &color);
};

} /* namespace GUI */

#endif /* SRC_RECT_H_ */
