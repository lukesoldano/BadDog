#include <gtest/gtest.h>

#include "EventPublisher.hpp"

struct TestEvent
{
   int m_value;
};

TEST(EventPublisher, Singleton) 
{
   ASSERT_NE(nullptr, &EventPublisher::instance());
}

TEST(EventPublisher, ReceiveEvent) 
{
   auto& event_publisher = EventPublisher::instance();

   bool event_received = false;
   int event_value = 5;
   EventPublisher::Callback<TestEvent> callback = [&event_value, &event_received](const TestEvent& i_event)
   {
      EXPECT_EQ(i_event.m_value, event_value);
      event_received = true;
   };

   event_publisher.subscribe_to_event<TestEvent>(TO_UINT_PTR(nullptr), callback);
   event_publisher.publish_event(TestEvent{event_value});
   ASSERT_TRUE(event_received);

   event_received = false;
   event_value = 10;
   event_publisher.publish_event(TestEvent{event_value});
   ASSERT_TRUE(event_received);

   event_publisher.unsubscribe_from_event<TestEvent>(TO_UINT_PTR(nullptr));
}

TEST(EventPublisher, ReceiveEventUsingMacros) 
{
   auto& event_publisher = EventPublisher::instance();

   bool event_received = false;
   int event_value = 5;
   EventPublisher::Callback<TestEvent> callback = [&event_value, &event_received](const TestEvent& i_event)
   {
      EXPECT_EQ(i_event.m_value, event_value);
      event_received = true;
   };

   SUBSCRIBE_TO_EVENT(TestEvent, nullptr, callback);
   PUBLISH_EVENT(TestEvent{event_value});
   ASSERT_TRUE(event_received);

   event_received = false;
   event_value = 10;
   PUBLISH_EVENT(TestEvent{event_value});
   ASSERT_TRUE(event_received);

   UNSUBSCRIBE_FROM_EVENT(TestEvent, nullptr);
}