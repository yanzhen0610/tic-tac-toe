/*
 * Text.h
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#ifndef SRC_TEXT_H_
#define SRC_TEXT_H_

#include "Displayable.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>

namespace GUI
{

class Text : public Displayable
{
public:
	Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
	Text(SDL_Renderer *renderer);
	virtual ~Text();

//	virtual void display();

	void setFontSize(int font_size);
	void setFont(const std::string &font_path);
	void setMessage(const std::string &message);
	virtual void setColor(const SDL_Color &color);

private:
	void openFont();
	virtual void createSurface();

private:
	std::string _message;
	SDL_Color _color;
	int _font_size = 0;
	std::string _font_path = "res/font/calibri.ttf";
	TTF_Font *_font = nullptr;
};

} /* namespace GUI */

#endif /* SRC_TEXT_H_ */
