/*
 * Clickable.h
 *
 *  Created on: Jun 3, 2017
 *      Author: yanzh
 */

#ifndef SRC_CLICKABLE_H_
#define SRC_CLICKABLE_H_

#include <SDL.h>

namespace GUI
{

class Clickable
{
public:
	Clickable();
	virtual ~Clickable();

	virtual inline void setClickAreaX(int x) { _x = x; }
	virtual inline void setClickAreaY(int y) { _y = y; }
	virtual inline void setClickAreaW(int w) { _w = w; }
	virtual inline void setClickAreaH(int h) { _h = h; }

	virtual inline int getClickAreaX() const { return _x; }
	virtual inline int getClickAreaY() const { return _y; }
	virtual inline int getClickAreaW() const { return _w; }
	virtual inline int getClickAreaH() const { return _h; }

	virtual bool isInClickArea(const int x, const int y) const;
	virtual void onClick(const SDL_Event &event) = 0;
	virtual void onTop(const SDL_Event &event) = 0;

protected:
	int _x = -1;
	int _y = -1;
	int _w = -1;
	int _h = -1;
};

} /* namespace GUI */

#endif /* SRC_CLICKABLE_H_ */
