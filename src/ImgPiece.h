/*
 * ImgPiece.h
 *
 *  Created on: Jun 2, 2017
 *      Author: yanzh
 */

#ifndef SRC_IMGPIECE_H_
#define SRC_IMGPIECE_H_

#include "AnimationEquation.h"
#include "Displayable.h"
#include "Image.h"

#include <string>
#include <chrono>

namespace GUI
{
namespace TTT
{

class ImgPiece: public Image
{
public:
	ImgPiece(SDL_Renderer *renderer, const std::string &piece_img_path);
	virtual ~ImgPiece();

	void show();
	void hide();

	virtual void display();

private:
	bool _is_shown = true;
	bool _is_animation_finished = false;
	std::chrono::time_point<std::chrono::system_clock> _animation_start_time;

private:
	static std::chrono::duration<int, std::nano> _duration_of_animation;
};

//std::chrono::duration<int, std::nano> ImgPiece::_duration_of_animation =
//		std::chrono::milliseconds(160);

} /* namespace TTT */
} /* namespace GUI */

#endif /* SRC_IMGPIECE_H_ */
