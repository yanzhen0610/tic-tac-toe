/*
 * Clickable.cpp
 *
 *  Created on: Jun 3, 2017
 *      Author: yanzh
 */

#include "Clickable.h"

#include <SDL.h>

namespace GUI
{

Clickable::Clickable()
{
}

Clickable::~Clickable()
{
	// TODO Auto-generated destructor stub
}

bool Clickable::isInClickArea(const int x, const int y) const
{
	if (x >= _x && x <= _x + _w && y >= _y && y <= _y + _h)
	{
		return true;
	}
	return false;
}

} /* namespace GUI */
