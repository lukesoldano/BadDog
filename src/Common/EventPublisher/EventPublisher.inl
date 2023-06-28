// Inlined within EventPublisher.hpp

#include "Logger.hpp"

#include <typeinfo>

namespace
{
   template <class EventType>
   struct Event : public BaseEvent
   {
      const EventType& m_event;

      Event(const EventType& i_event) :
         m_event(i_event) {}

      static size_t get_type_id()
      {
         static size_t id = get_next_type_id();
         return id;
      }

   };

   template <class EventType>
   struct CallbackWrapper
   {
      EventPublisher::Callback<EventType> m_callback;

      CallbackWrapper(EventPublisher::Callback<EventType> i_callback) :
         m_callback(i_callback) {}

      void operator()(const BaseEvent& i_event)
      {
         m_callback(static_cast<const Event<EventType>&>(i_event).m_event);
      }
   };

}

template <class EventType>
void EventPublisher::publish_event(const EventType& i_event)
{
   const auto event_type_id = Event<EventType>::get_type_id();
   if (event_type_id >= m_subscribers.size() || m_subscribers[event_type_id].empty())
   {
      LOG_WARNING("Published an event type no one is listening for, type id: " << 
                  event_type_id << 
                  ", mangled type name: " << 
                  typeid(EventType).name());
   }
   else
   {
      Event<EventType> wrapped_event{i_event};
      for (auto& subscriber : m_subscribers[event_type_id])
      {
         subscriber.second(wrapped_event);
      }
   }

}

template <class EventType>
void EventPublisher::subscribe_to_event(EntityId i_id, Callback<EventType> i_callback)
{
   const auto event_type_id = Event<EventType>::get_type_id();
   if (event_type_id >= m_subscribers.size())
   {
      m_subscribers.resize(event_type_id + 1);
   }

   CHECK_CONDITION_RETURN_VOID(m_subscribers[event_type_id].find(i_id) == 
                               m_subscribers[event_type_id].end());

   m_subscribers[event_type_id][i_id] = CallbackWrapper<EventType>{i_callback};
}

template <class EventType>
void EventPublisher::unsubscribe_from_event(EntityId i_id)
{
   const auto event_type_id = Event<EventType>::get_type_id();
   if (event_type_id < m_subscribers.size())
   {
      m_subscribers[event_type_id].erase(i_id);
   }
}