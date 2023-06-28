#pragma once

#include "ProjectDefs.hpp"

#include <functional>
#include <unordered_map>
#include <vector>

// This implementation is heavily inspired by the StackOverflow design post:
// https://codereview.stackexchange.com/questions/79211/ecs-event-messaging-implementation

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
   std::vector<std::unordered_map<EntityId, Callback<BaseEvent>>> m_subscribers;

public:

   EventPublisher() = default;
   virtual ~EventPublisher() = default;

   template <class EventType>
   void publish_event(const EventType& i_event);

   template <class EventType>
   void subscribe_to_event(EntityId i_id, Callback<EventType> i_callback);

   template <class EventType>
   void unsubscribe_from_event(EntityId i_id);

};

#include "EventPublisher.inl"