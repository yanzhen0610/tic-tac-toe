/*
 * Displayable.cpp
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#include "Displayable.h"

#include <SDL.h>

#include <iostream>

namespace GUI
{

//Displayable::Displayable(SDL_Renderer *renderer) :
//		_renderer(renderer)
//{
//}

Displayable::~Displayable()
{
	if (_surface != nullptr)
	{
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}
	if (_texture != nullptr)
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
}

void Displayable::display()
{
	if (_texture != nullptr && _is_display)
	{
		SDL_RenderCopyEx(_renderer, _texture, nullptr, &_rect, _rotate_angle,
				&_rotate_point, _flip);
	}
}

void Displayable::createSurface()
{
	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, 0, 0, 32,
			SDL_PIXELFORMAT_ARGB32);
	if (surface != nullptr)
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
		}
		_surface = surface;
	}
}

void Displayable::createTexture()
{
	if (_surface != nullptr)
	{
		SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer,
				_surface);
		if (texture != nullptr)
		{
			if (_texture != nullptr)
			{
				SDL_DestroyTexture(_texture);
			}
			_texture = texture;
			SDL_QueryTexture(_texture, nullptr, nullptr, &_rect.w, &_rect.h);
			return;
		}
	}
	std::cerr << "failed to create new texture.\n";
}

void Displayable::setAlpha(int alpha)
{
	if (_texture != nullptr)
	{
		if (!SDL_SetTextureAlphaMod(_texture, alpha))
		{
			_alpha = alpha;
		}
		else
		{
			std::cerr << "failed to set alpha to " << alpha << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to set alpha: texture not exist\n";
	}
}

} /* namespace GUI */
