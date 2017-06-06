/*
 * ImgPiece.cpp
 *
 *  Created on: Jun 2, 2017
 *      Author: yanzh
 */

#include "AnimationEquation.h"
#include "Displayable.h"
#include "Image.h"
#include "ImgPiece.h"

#include <string>
#include <chrono>

namespace GUI
{
namespace TTT
{

std::chrono::duration<int, std::nano> ImgPiece::_duration_of_animation =
		std::chrono::milliseconds(160);

ImgPiece::ImgPiece(SDL_Renderer *renderer, const std::string &piece_img_path) :
		Image(renderer, piece_img_path)
{
	// TODO Auto-generated constructor stub

}

ImgPiece::~ImgPiece()
{
	// TODO Auto-generated destructor stub
}

void ImgPiece::display()
{
	if (_is_display)
	{
		if (!_is_animation_finished)
		{
			std::chrono::time_point<std::chrono::system_clock> now =
					std::chrono::system_clock::now();
			if (now - _animation_start_time < _duration_of_animation)
			{
				setAlpha(
						squareRootAnimate((now - _animation_start_time).count(),
								0, _duration_of_animation.count(), 0, 255));
			}
			else
			{
				setAlpha(255);
				_is_animation_finished = true;
			}
		}
		Displayable::display();
	}
}

void ImgPiece::show()
{
	setVisible(true);
	_animation_start_time = std::chrono::system_clock::now();
}

void ImgPiece::hide()
{
	setVisible(false);
	_is_animation_finished = false;
}

} /* namespace TTT */
} /* namespace GUI */
