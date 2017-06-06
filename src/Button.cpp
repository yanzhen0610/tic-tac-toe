/*
 * Button.cpp
 *
 *  Created on: Jun 5, 2017
 *      Author: yanzh
 */

#include "Button.h"

#include "Clickable.h"
#include "Displayable.h"
#include "Text.h"
#include "Rect.h"

#include <SDL.h>

#include <string>
#include <mutex>
#include <map>
#include <vector>
#include <functional>
#include <exception>

namespace GUI
{

Button::Button(SDL_Renderer *renderer) :
		Displayable(renderer), _button_text(renderer), _button_background(
				renderer)
{
	// TODO Auto-generated constructor stub

}

Button::~Button()
{
	// TODO Auto-generated destructor stub
}

void Button::setMargin(int margin)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_margin = margin;
	_button_text.setPosition(_x + _margin, _y + _margin);
	_w = _button_text.getRect().w + _margin * 2;
	_h = _button_text.getRect().h + _margin * 2;
}

void Button::setPosition(int x, int y)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_x = x;
	_y = y;
	_button_background.setPosition(_x, _y);
	_button_text.setPosition(x + _margin, y + _margin);
}

void Button::setButtonTextFontSize(int size)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_button_text.setFontSize(size);
	_button_background.setWidthNLength(_button_text.getRect().w + _margin * 2,
			_button_text.getRect().h + _margin * 2);
	_w = _button_text.getRect().w + _margin * 2;
	_h = _button_text.getRect().h + _margin * 2;

}

void Button::display()
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_button_background.display();
	_button_text.display();
}

void Button::onClick(const SDL_Event &event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		try
		{
			for (std::function<void()> f : _mouse_button_action_list.at(
					event.button.button))
			{
				f();
			}
		} catch (const std::out_of_range &e)
		{
		}
	}
}

void Button::onTop(const SDL_Event &event)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	for (std::function<void()> f : _on_top_action_list)
	{
		f();
	}
}

void Button::setButtonAction(const Uint8 button,
		const std::vector<std::function<void()>> &action_list)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_mouse_button_action_list[button] = action_list;
}

void Button::addButtonAction(const Uint8 button,
		const std::function<void()> &action)
{
	std::lock_guard<std::mutex> lock(_modification_mutex);
	_mouse_button_action_list[button].push_back(action);
}

void Button::setOnTopAction(
		const std::vector<std::function<void()>> &action_list)
{
	std::lock_guard<std::mutex> locl(_modification_mutex);
	_on_top_action_list = action_list;
}

void Button::addOnTopAction(
		const std::function<void()> &action)
{
	std::lock_guard<std::mutex> locl(_modification_mutex);
	_on_top_action_list.push_back(action);
}

} /* namespace GUI */
