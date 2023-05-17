#include "EventDispatcher.h"
#include "Event.h"

using namespace events;

void EventDispatcher::emit(const Event& e)
{
	EventMap copy(_eventMap);
	auto range = copy.equal_range(&typeid(e));
	for (auto it = range.first; it != range.second; it++) {
		it->second.f(e);
	}
}
