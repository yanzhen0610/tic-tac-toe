/*
 * Text.cpp
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#include "Text.h"
#include "Displayable.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>

namespace GUI
{

Text::Text(SDL_Renderer *renderer, const std::string &font_path, int font_size,
		const std::string &message_text, const SDL_Color &color) :
		Displayable(renderer), _message(message_text), _color(color), _font_size(
				font_size), _font_path(font_path)
{
	openFont();
	createSurface();
	createTexture();
}

Text::Text(SDL_Renderer *renderer) : Displayable(renderer)
{
}

Text::~Text()
{
	if (_font != nullptr)
	{
		TTF_CloseFont(_font);
		_font = nullptr;
	}
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

void Text::openFont()
{
	TTF_Font *font = TTF_OpenFont(_font_path.c_str(), _font_size);
	if (font != nullptr)
	{
		if (_font != nullptr)
		{
			TTF_CloseFont(_font);
		}
		_font = font;
	}
	else
	{
		std::cerr << "unable to load font " << _font_path << std::endl;
	}
}

void Text::createSurface()
{
	if (_font != nullptr)
	{
		SDL_Surface *surface = TTF_RenderText_Blended(_font, _message.c_str(), _color);
		if (surface != nullptr)
		{
			if (_surface != nullptr)
			{
				SDL_FreeSurface(_surface);
			}
			_surface = surface;
		}
	}
}

void Text::setFontSize(int font_size)
{
	const int origin_font_size = _font_size;
	_font_size = font_size;
	openFont();
	if (_font == nullptr)
	{
		_font_size = origin_font_size;
		openFont();
	}
	createSurface();
	createTexture();
}

void Text::setFont(const std::string &font_path)
{
	const std::string origin_font_path = _font_path;
	_font_path = font_path;
	openFont();
	if (_font == nullptr)
	{
		_font_path = origin_font_path;
		openFont();
	}
	createSurface();
	createTexture();
}

void Text::setMessage(const std::string &message)
{
	_message = message;
	createSurface();
	createTexture();
}

void Text::setColor(const SDL_Color &color)
{
//	Displayable::setColor(color);
	_color = color;
	createSurface();
	createTexture();
}

} /* namespace GUI */
