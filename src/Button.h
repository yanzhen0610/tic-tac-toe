/*
 * Button.h
 *
 *  Created on: Jun 5, 2017
 *      Author: yanzh
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

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

namespace GUI
{

class Button: public Displayable, public Clickable
{
public:
	Button(SDL_Renderer *renderer);
	virtual ~Button();

	void setButtonTextFontSize(int size);
	virtual void setPosition(int x, int y);

	void setMargin(int margin);
	inline void setButtonText(const std::string &text)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		_button_text.setMessage(text);
	}
	inline void setButtonTextColor(const SDL_Color &color)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		_button_text.setColor(color);
	}
	inline void setButtonBackgroundColor(const SDL_Color &color)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		_button_background.setColor(color);
	}

	inline void showText(bool isShow = true)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		_button_text.setVisible(isShow);
	}
	inline void shwoBackground(bool isShow = true)
	{
		std::lock_guard<std::mutex> lock(_modification_mutex);
		_button_background.setVisible(isShow);
	}

	virtual void display();

	virtual void onClick(const SDL_Event &event);
	virtual void onTop(const SDL_Event &event);

	virtual void setButtonAction(const Uint8 button,
			const std::vector<std::function<void()>> &action_list);
	virtual void addButtonAction(const Uint8 button,
			const std::function<void()> &action);
	virtual void setOnTopAction(
			const std::vector<std::function<void()>> &action_list);
	virtual void addOnTopAction(
			const std::function<void()> &action);

private:
	std::mutex _modification_mutex;
	std::map<Uint8, std::vector<std::function<void()>>>_mouse_button_action_list;
	std::vector<std::function<void()>> _on_top_action_list;

	Text _button_text;
	Rect _button_background;
	int _margin = 10;
};

}
/* namespace GUI */

#endif /* SRC_BUTTON_H_ */
