/*
 * Image.h
 *
 *  Created on: May 31, 2017
 *      Author: yanzh
 */

#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#include "Displayable.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <chrono>

namespace GUI
{

class Image: public Displayable
{
public:
	Image(SDL_Renderer *renderer, const std::string &image_path);
	virtual ~Image();

	virtual void createSurface();

private:
	std::string _image_path;
};

} /* namespace GUI */

#endif /* SRC_IMAGE_H_ */
