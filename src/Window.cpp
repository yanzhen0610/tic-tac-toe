/*
 * Window.cpp
 *
 *  Created on: May 29, 2017
 *      Author: yanzh
 */

#include "Window.h"
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

std::mutex Window::_init_lock;

Window::Window(const std::string &title, int width, int height) :
		_title(title), _width(width), _height(height)
{
	_closed = !init();
	create();
}

Window::~Window()
{
	destroy();
}

void Window::create()
{
	std::cout << "Thread " << std::this_thread::get_id()
			<< " Window::create()\n";
	if (_closed)
	{
		std::cout << "Thread " << std::this_thread::get_id()
				<< " exit Window::create(): closed\n";
		return;
	}

	if (_window == nullptr)
	{
		// create a window
		std::cout << "Thread " << std::this_thread::get_id()
				<< " Window::create(): SDL_CreateWindow()\n";
		_window = SDL_CreateWindow(_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _width, _height, 0);
		if (_window == nullptr)
		{
			std::cerr << "Failed to create window.\n";
			_closed = true;
			return;
		}
		else
		{
			// get window id
			std::cout << "Thread " << std::this_thread::get_id()
					<< " Window::create(): SDL_GetWindowID()\n";
			_window_id = SDL_GetWindowID(_window);

			if (_renderer == nullptr)
			{
				// create renderer
				std::cout << "Thread " << std::this_thread::get_id()
						<< " Window " << _window_id
						<< " Window::create(): SDL_CreateRenderer()\n";
				_renderer = SDL_CreateRenderer(_window, -1,
						SDL_RENDERER_ACCELERATED);
				if (_renderer == nullptr)
				{
					std::cerr << "Failed to create renderer.\n";
					_closed = true;
					return;
				}

				// create FPS monitor
				EventHandler::addHandler(std::this_thread::get_id(), this);
				std::lock_guard<std::mutex> lock(
						_frames_per_second_monitor_modification_mutex);
				_frames_per_second_monitor = new Text(_renderer,
						"res/font/calibri.ttf", 20, "0",
						{ 0, 255, 0, 255 });
				if (_frames_per_second_monitor != nullptr)
				{
					_frames_per_second_monitor->setPosition(10, 10);
				}
				else
				{
					std::cerr << "Thread " << std::this_thread::get_id()
							<< " Window " << _window_id
							<< " failed to create fps monitor\n";
				}
			}
		}
	}
}

void Window::destroy()
{
	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " Window::destroy()\n";
	_closed = true;
	EventHandler::removeHandler(this);

	// wait for sub-threads ended
	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " wait for sub-threads join";
	join();

	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " destroy fps monitor\n";
	{
		std::lock_guard<std::mutex> lock(
				_frames_per_second_monitor_modification_mutex);
		removeDisplayable(_frames_per_second_monitor);
		if (_frames_per_second_monitor != nullptr)
		{
			delete _frames_per_second_monitor;
			_frames_per_second_monitor = nullptr;
		}
	}

	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " destroy renderer\n";
	if (_renderer != nullptr)
	{
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}

	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " destroy window\n";
	if (_window_thread_id == std::this_thread::get_id())
	{
		if (_window != nullptr)
		{
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
	}

	std::cout << "Thread " << std::this_thread::get_id() << " Window "
			<< _window_id << " end Window::destroy()\n";
}

void thread_event(Window *w)
{
	while (!w->isClosed())
	{
		w->pollEvent();
	}
	std::cout << "end thread_event\n";
}

void thread_display(Window *w)
{
	using std::chrono::time_point;
	using std::chrono::system_clock;
	using namespace std::chrono_literals;

	time_point<system_clock> time_to_next_frame;
	time_point<system_clock> time_of_last_frame;
	std::chrono::duration<int, std::nano> duration_time_from_last_frame;
	time_of_last_frame = system_clock::now() - 1s;

	while (!w->isClosed())
	{
		duration_time_from_last_frame = system_clock::now()
				- time_of_last_frame;
		if (duration_time_from_last_frame > 0s)
		{
			w->_frames_per_second = 1s / duration_time_from_last_frame;
		}
		else
		{
			w->_frames_per_second = 0;
		}
		time_of_last_frame = system_clock::now();
		time_to_next_frame = system_clock::now()
				+ std::chrono::milliseconds(16);

		w->nextFrame();
		if (w->_is_locking_fps_to_60)
		{
			std::this_thread::sleep_until(time_to_next_frame);
		}
	}
	std::cout << "thread_display is ended\n";
}

void Window::start()
{
	if (!_closed)
	{
		std::lock_guard<std::mutex> lock(_thread_modification_mutex);
		if (_thread_event_handler == nullptr)
		{
			_thread_event_handler = new std::thread(thread_event, this);
		}
		if (_thread_display == nullptr)
		{
			_thread_display = new std::thread(thread_display, this);
		}
	}
}

void Window::join()
{
	std::cout << std::this_thread::get_id() << "Window::join()\n";
	std::lock_guard<std::mutex> lock(_thread_modification_mutex);
	std::cout << "Window::join() _thread_display\n";
	if (_thread_display != nullptr)
	{
		if (_thread_display->get_id() != std::this_thread::get_id())
		{
			if (_thread_display->joinable())
			{
				_thread_display->join();
				delete _thread_display;
				_thread_display = nullptr;
			}
		}
	}
	std::cout << "Window::join() _thread_event_handler\n";
	if (_thread_event_handler != nullptr)
	{
		if (_thread_event_handler->get_id() != std::this_thread::get_id())
		{
			if (_thread_event_handler->joinable())
			{
				std::cout << "Window::join() _thread_event_handler->join()\n";
				_thread_event_handler->join();
				std::cout
						<< "Window::join() _thread_event_handler->join() quit\n";
				delete _thread_event_handler;
				_thread_event_handler = nullptr;
			}
		}
	}
	std::cout << std::this_thread::get_id() << "end Window::join()\n";
}

void Window::pollEvent()
{
	if (!isClosed())
	{
		SDL_Event event = getEvent();
		if (event.window.windowID == _window_id)
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					std::cout << "close\n";
					destroy();
					break;
				}
				break;

			case SDL_QUIT:
				std::cout << "quit\n";
				destroy();
				break;

			case SDL_MOUSEBUTTONDOWN:
			{
				std::lock_guard<std::mutex> lock(_clickable_list_mutex);
				for (int i = _clickable_list.size() - 1; i >= 0; --i)
				{
					Clickable *clickable = _clickable_list.at(i);
					if (clickable->isInClickArea(event.motion.x, event.motion.y))
					{
						clickable->onClick(event);
					}
				}
			}
				break;

			case SDL_MOUSEBUTTONUP:
			{
				std::lock_guard<std::mutex> lock(_clickable_list_mutex);
				for (int i = _clickable_list.size() - 1; i >= 0; --i)
				{
					Clickable *clickable = _clickable_list.at(i);
					if (clickable->isInClickArea(event.motion.x, event.motion.y))
					{
						clickable->onClick(event);
					}
				}
			}
				break;

			case SDL_MOUSEMOTION:
			{
				std::lock_guard<std::mutex> lock(_clickable_list_mutex);
				for (int i = _clickable_list.size() - 1; i >= 0; --i)
				{
					Clickable *clickable = _clickable_list.at(i);
					if (clickable->isInClickArea(event.motion.x, event.motion.y))
					{
						clickable->onTop(event);
					}
				}
			}
				break;
			}
		}
	}
}

void Window::nextFrame()
{
	if (SDL_SetRenderDrawColor(_renderer, 20, 189, 172, 255) == 0)
	{
	}
	else
	{
		std::cerr << "failed to set render draw color\n" << SDL_GetError()
				<< std::endl;
	}
	if (SDL_RenderClear(_renderer) == 0)
	{
	}
	else
	{
		std::cerr << "Failed to clear renderer\n" << SDL_GetError()
				<< std::endl;
	}

	{
		std::lock_guard<std::mutex> lock(_display_list_mutex);
		for (Displayable* obj : _display_list)
		{
			obj->display();
		}
	}

	if (_is_showing_frames_per_second_monitor)
	{
		std::lock_guard<std::mutex> lock(
				_frames_per_second_monitor_modification_mutex);
		_frames_per_second_monitor->setMessage(
				std::to_string(_frames_per_second));
		_frames_per_second_monitor->display();
	}
	SDL_RenderPresent(_renderer);
}

void Window::addDisplayable(Displayable *displayable)
{
	std::lock_guard<std::mutex> lock(_display_list_mutex);
	_display_list.push_back(displayable);
}

void Window::removeDisplayable(Displayable *displayable)
{
	std::lock_guard<std::mutex> lock(_display_list_mutex);
	for (std::vector<Displayable*>::iterator it = _display_list.begin();
			it != _display_list.end();)
	{
		if (*it == displayable)
		{
			it = _display_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Window::addClickable(Clickable *clickable)
{
	std::lock_guard<std::mutex> lock(_clickable_list_mutex);
	_clickable_list.push_back(clickable);
}

void Window::removeClickable(Clickable *clickable)
{
	std::lock_guard<std::mutex> lock(_clickable_list_mutex);
	for (std::vector<Clickable*>::iterator it = _clickable_list.begin();
			it != _clickable_list.end();)
	{
		if (*it == clickable)
		{
			it = _clickable_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Window::init()
{
	std::lock_guard<std::mutex> guard(Window::_init_lock);

	_window_thread_id = std::this_thread::get_id();

	std::cout << "Thread " << std::this_thread::get_id() << " SDL_Init()\n";
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to initialize SDL video.\n";
		return false;
	}

	std::cout << "Thread " << std::this_thread::get_id() << " TTF_Init()\n";
	if (TTF_Init() == -1)
	{
		std::cerr << "Thread " << std::this_thread::get_id()
				<< "failed to initialize SDL_ttf.\n";
		return false;
	}

	std::cout << "Thread " << std::this_thread::get_id()
			<< " IMG_Init(IMG_INIT_PNG)\n";
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Thread " << std::this_thread::get_id()
				<< "Failed to initialize image_png.\n";
		return false;
	}

	return true;
}

} /* namespace GUI */
