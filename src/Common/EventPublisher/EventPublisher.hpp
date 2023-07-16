#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <vector>

// This implementation is heavily inspired by the StackOverflow design post:
// https://codereview.stackexchange.com/questions/79211/ecs-event-messaging-implementation

// Some ugly macros to make subscribing to events easier and less verbose in line
// Macros for subscribing to events with a loose object and callback
#define SUBSCRIBE_TO_EVENT(event_type, ptr, callback) \
   EventPublisher::instance().subscribe_to_event<event_type>(TO_UINT_PTR(ptr), callback)

#define UNSUBSCRIBE_FROM_EVENT(event_type, ptr) \
   EventPublisher::instance().unsubscribe_from_event<event_type>(TO_UINT_PTR(ptr))

// Macros for subscribing to events with a member function
#define M_SUBSCRIBE_TO_EVENT(event_type, callback) \
   EventPublisher::instance().subscribe_to_event<event_type>(TO_UINT_PTR(this), [this](const auto& i_event){ this->callback(i_event); })

#define M_UNSUBSCRIBE_FROM_EVENT(event_type) \
   EventPublisher::instance().unsubscribe_from_event<event_type>(TO_UINT_PTR(this))

struct BaseEvent
{
   virtual ~BaseEvent() = default;

protected:

   static size_t get_next_type_id()
   {
      static size_t id = 0;
      return id++;
   }

};

class EventPublisher
{
public:

   template <class EventType>
   using Callback = std::function<void(const EventType&)>;

private:

   // Vector position correlates with event type id
   std::vector<std::unordered_map<std::uintptr_t, Callback<BaseEvent>>> m_subscribers;

public:

   inline static EventPublisher& instance();

   void publish_event(auto&& i_event);

   template <class EventType>
   void subscribe_to_event(std::uintptr_t i_subscriber, Callback<EventType> i_callback);

   template <class EventType>
   void unsubscribe_from_event(std::uintptr_t i_subscriber);

private:

   EventPublisher() = default;
   virtual ~EventPublisher() = default;

};

#include "EventPublisher.inl"