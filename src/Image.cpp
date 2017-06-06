/*
 * Image.cpp
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#include "Image.h"
#include "AnimationEquation.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <chrono>

namespace GUI
{

Image::Image(SDL_Renderer *renderer, const std::string &image_path) :
		Displayable(renderer), _image_path(image_path)
{
	createSurface();
	createTexture();
}

Image::~Image()
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

void Image::createSurface()
{
	SDL_Surface *surface = IMG_Load(_image_path.c_str());
	if (surface != nullptr)
	{
		if (_surface != nullptr)
		{
			SDL_FreeSurface(_surface);
		}
		_surface = surface;
	}
	else
	{
		std::cerr << "Failed to load image: " << _image_path << "\n";
	}
}

} /* namespace GUI */
