/*
 * Rect.cpp
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#include "Displayable.h"
#include "Rect.h"

#include <SDL.h>

#include <iostream>

namespace GUI
{

Rect::Rect(SDL_Renderer *renderer) :
		Displayable(renderer)
{
	createSurface();
	createTexture();
}

Rect::Rect(SDL_Renderer *renderer, const SDL_Color &color, int w, int h) :
		Displayable(renderer)
{
	Displayable::setColor(color);
	Displayable::setWidthNLength(w, h);
	createSurface();
	createTexture();
}

Rect::~Rect()
{
	if (_surface != nullptr)
	{
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}
}

void Rect::createSurface()
{
	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, _rect.w, _rect.h,
			32, SDL_PIXELFORMAT_ARGB32);
	if (surface != nullptr)
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
		}
		_surface = surface;
		if (SDL_FillRect(_surface, 0,
				SDL_MapRGBA(_surface->format, _color.r, _color.g, _color.b,
						_color.a)) == 0)
		{
			return;
		}
	}
	std::cerr << "Failed to create surface: rect\n";
}

void Rect::setColor(const SDL_Color &color)
{
	Displayable::setColor(color);
	createSurface();
	createTexture();
}

} /* namespace GUI */
