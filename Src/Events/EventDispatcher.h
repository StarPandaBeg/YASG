#pragma once

#include "Event.h"

#include <functional>
#include <map>
#include <typeinfo>

namespace events {
	struct EventObject {
		int id = -1;
		std::function<void(const Event&)> f;
	};
	typedef std::multimap<const std::type_info*, EventObject> EventMap;

	class EventDispatcher
	{
	private:
		EventMap _eventMap;
	protected:
		void emit(const Event&);
	public:
		virtual ~EventDispatcher() {};

		template<typename EventWanted>
		int on(const std::function<void(const Event&)>&);

		template<typename EventWanted>
		void off(int id);
	};

	template<typename EventWanted>
	inline int EventDispatcher::on(const std::function<void(const Event&)>& fn)
	{
		int id = rand() % 10000000;
		auto evObj = EventObject();
		evObj.id = id;
		evObj.f = fn;

		_eventMap.emplace(&typeid(EventWanted), evObj);
		return id;
	}

	template<typename EventWanted>
	inline void EventDispatcher::off(int id)
	{
		auto range = _eventMap.equal_range(&typeid(EventWanted));
		auto it = range.first;
		for (; it != range.second; ++it) {
			if (it->second.id == id) break;
		}
		if (it == range.second) return;

		_eventMap.erase(it->first);
	}
}

