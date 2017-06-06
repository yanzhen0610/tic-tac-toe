/*
 * Window.h
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "Clickable.h"
#include "Displayable.h"
#include "EventHandler.h"
#include "Text.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>

namespace GUI
{

class Window : public EventHandler
{
public:
	Window(const std::string &title, int width, int height);
	virtual ~Window();

	virtual void start();
	virtual void join();

	virtual void pollEvent();
	virtual void nextFrame();

	inline SDL_Renderer* getRenderer() { return _renderer; }
	inline bool isClosed() const { return _closed; }
	inline void showFPS(bool isShowing = false) { _is_showing_frames_per_second_monitor = isShowing; }
	inline void setMaxFPSto60(bool is60 = true) { _is_locking_fps_to_60 = is60; }
	void addDisplayable(Displayable *displayable);
	void removeDisplayable(Displayable *displayable);
	void addClickable(Clickable *clickable);
	void removeClickable(Clickable *clickable);

protected:
	inline SDL_Window* getWindow() { return _window; }

	void create();
	void destroy();

private:
	bool init();

	friend void thread_display(Window *w);
	friend void thread_event(Window *w);

private:
	int _frames_per_second = 0;
	bool _is_showing_frames_per_second_monitor = false;
	std::mutex _frames_per_second_monitor_modification_mutex;
	Text *_frames_per_second_monitor = nullptr;
	bool _is_locking_fps_to_60 = true;

	std::string _title;
	int _width = 800;
	int _height = 600;

	bool _closed = false;

	std::mutex _clickable_list_mutex;
	std::mutex _display_list_mutex;
	std::vector<Displayable*> _display_list;
	std::vector<Clickable*> _clickable_list;

	std::thread *_thread_display = nullptr;
	std::thread *_thread_event_handler = nullptr;
	std::mutex _thread_modification_mutex;

protected:
	Uint32 _window_id = 0xffffffff;
	SDL_Window *_window = nullptr;
	std::thread::id _window_thread_id;
	SDL_Renderer *_renderer = nullptr;

private:
	static std::mutex _init_lock;
};

} /* namespace GUI */

#endif /* WINDOW_H_ */
