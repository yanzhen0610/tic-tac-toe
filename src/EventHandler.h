/*
 * EventHandler.h
 *
 *  Created on: May 30, 2017
 *      Author: yanzh
 */

#ifndef SRC_EVENTHANDLER_H_
#define SRC_EVENTHANDLER_H_

#include <SDL.h>

#include <map>
#include <set>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

namespace GUI
{

class EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler();

	void addEvent(const SDL_Event &event);
	const SDL_Event getEvent();

	static void addHandler(const std::thread::id &thread_id, EventHandler *handler);
	static void removeHandler(EventHandler *handler);
	// end after all handler closed
	static void startHandling();

//	struct Handler
//	{
//
//	};

private:
	static bool isContainsAnyHandler();

private:
	std::mutex _event_mutex;
	std::timed_mutex _waiting_mutex;
	std::vector<SDL_Event> _event_list;

	static std::mutex _handler_modification_mutex;
	static std::map<std::thread::id, std::set<EventHandler*>> _handlers;
};

} /* namespace GUI */

#endif /* SRC_EVENTHANDLER_H_ */
