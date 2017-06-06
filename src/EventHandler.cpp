/*
 * EventHandler.cpp
 *
 *  Created on: May 30, 2017
 *      Author: yanzh
 */

#include "EventHandler.h"

#include <SDL.h>

#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

namespace GUI
{

std::map<std::thread::id, std::set<EventHandler*>> EventHandler::_handlers;
std::mutex EventHandler::_handler_modification_mutex;

EventHandler::EventHandler()
{
	// TODO Auto-generated constructor stub

}

EventHandler::~EventHandler()
{
	// TODO Auto-generated destructor stub
}

void EventHandler::addEvent(const SDL_Event &event)
{
	_waiting_mutex.unlock();
	std::lock_guard<std::mutex> lock(_event_mutex);

	_event_list.push_back(event);
}

const SDL_Event EventHandler::getEvent()
{
	while (true)
	{
		_waiting_mutex.unlock();
		_event_mutex.lock();
		if (_event_list.size() > 0)
		{
			SDL_Event event = _event_list.at(0);
			_event_list.erase(_event_list.begin());
			_event_mutex.unlock();
			return event;
		}
		_event_mutex.unlock();
		_waiting_mutex.try_lock_for(std::chrono::milliseconds(1));
		_waiting_mutex.try_lock_for(std::chrono::milliseconds(1));
	}
}

void EventHandler::addHandler(const std::thread::id &thread_id,
		EventHandler *handler)
{
	std::lock_guard<std::mutex> lock(_handler_modification_mutex);
	_handlers[thread_id].insert(handler);
}

void EventHandler::removeHandler(EventHandler *handler)
{
	std::lock_guard<std::mutex> lock(_handler_modification_mutex);
	for (std::map<std::thread::id, std::set<EventHandler*>>::iterator iteratori =
			_handlers.begin(); iteratori != _handlers.end(); ++iteratori)
	{
		for (std::set<EventHandler*>::iterator iteratorj =
				iteratori->second.begin(); iteratorj != iteratori->second.end();
				)
		{
			if (*iteratorj == handler)
			{
				iteratorj = iteratori->second.erase(iteratorj);
			}
			else
			{
				++iteratorj;
			}
		}
	}
}

void EventHandler::startHandling()
{
	SDL_Event event;
	std::set<EventHandler*> handler_set;

	while (isContainsAnyHandler())
	{
		while (SDL_WaitEventTimeout(&event, 1))
		{
			std::lock_guard<std::mutex> lock(_handler_modification_mutex);
//			_handler_modification_mutex.lock();
			for (std::pair<std::thread::id, std::set<EventHandler*>> thread_handler_pair : _handlers)
			{
				handler_set = thread_handler_pair.second;
				for (EventHandler *handler : handler_set)
				{
					handler->addEvent(event);
				}
			}
//			_handler_modification_mutex.unlock();
		}
	}
}

bool EventHandler::isContainsAnyHandler()
{
	std::lock_guard<std::mutex> lock(_handler_modification_mutex);
	std::set<EventHandler*> handler_set = _handlers[std::this_thread::get_id()];

	if (handler_set.size() > 0)
	{
		return true;
	}
	return false;
}

} /* namespace GUI */
