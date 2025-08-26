#include "EnginePCH.h"
#include "Core/StringHelper.h"
namespace claw {
	void EventManager::AddObserver(const Event::id_t id, IObserver& observer)
	{
		m_observers[toLower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer)
	{
		IObserver* observerPtr = &observer;
		// go through all event types
		for (auto& eventType : m_observers) {
			// get list of observers for this event type
			auto& observers = eventType.second;

			//remove matching observers from event type
			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event)
	{
		//find observers for this event type
		auto iter = m_observers.find(toLower(event.id));
		if (iter != m_observers.end()) {
			//get observers for event type
			auto& observers = iter->second;
			for (auto observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("No observers found for event {} " , event.id);
		}
	}
}

