/*
 * Displayable.h
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#ifndef SRC_DISPLAYABLE_H_
#define SRC_DISPLAYABLE_H_

#include <SDL.h>

#include <iostream>

namespace GUI
{

class Displayable
{
public:
	inline Displayable(SDL_Renderer *renderer) : _renderer(renderer) { };
	virtual ~Displayable();

	virtual void display();

	virtual inline void setVisible(bool isDisplay = true) { _is_display = isDisplay; }

	virtual inline void setPosition(int x, int y) { _rect.x = x; _rect.y = y; }
	virtual inline void setWidthNLength(int w, int h) { _rect.w = w, _rect.h = h; }
	virtual inline void setX(int x) { _rect.x = x; }
	virtual inline void setY(int y) { _rect.y = y; }
	virtual inline void setW(int w) { _rect.w = w; }
	virtual inline void setH(int h) { _rect.h = h; }
//	inline int getX() const { return _rect.x; }
//	inline int getY() const { return _rect.y; }
//	inline int getW() const { return _rect.w; }
//	inline int getH() const { return _rect.h; }
	inline const SDL_Rect& getRect() const { return _rect; }

	virtual inline void setColor(const SDL_Color &color) { _color = color; }
	virtual inline const SDL_Color& getColor() const { return _color; }

	virtual void setAlpha(int alpha);
	virtual inline int getAlpha() const { return _alpha; }

	virtual inline void setRenderer(SDL_Renderer *renderer) { _renderer = renderer; }
	virtual inline SDL_Renderer* getRenderer() const { return _renderer; }

	virtual inline void setFlip(const SDL_RendererFlip &flip) { _flip = flip; }
	virtual inline const SDL_RendererFlip& getFlip() const { return _flip; }

	virtual inline void setRotatePoint(const SDL_Point &point) { _rotate_point = point; }
	virtual inline const SDL_Point& getRotatePoint() const { return _rotate_point; }

	virtual inline void setRotateAngle(double angle) { _rotate_angle = angle; }
	virtual inline double getRotateAngle() const { return _rotate_angle; }

protected:
	virtual void createSurface();
	virtual void createTexture();

protected:
	SDL_Color _color = { 0, 0, 0, 0 };
	SDL_Rect _rect = { 0, 0, 0, 0 };
	SDL_Renderer *_renderer = nullptr;
	SDL_Surface *_surface = nullptr;
	SDL_Texture *_texture = nullptr;
	SDL_RendererFlip _flip = SDL_FLIP_NONE;
	SDL_Point _rotate_point = { 0, 0 };
	double _rotate_angle = 0.0;
	int _alpha = 255;
	bool _is_display = true;
};

} /* namespace GUI */

#endif /* SRC_DISPLAYABLE_H_ */
