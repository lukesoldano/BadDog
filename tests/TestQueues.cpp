#include <gtest/gtest.h>

#include "ImmediateQueue.hpp"

struct TestEvent
{
   int m_value;
};

TEST(ImmediateQueue, ReceiveEvent) 
{
   int value = 5;
   bool event_received = false;
   std::function<void(const TestEvent&)> callback = [&value, &event_received](const TestEvent& i_event)
   {
      EXPECT_EQ(i_event.m_value, value);
      event_received = true;
   };

   ImmediateQueue queue(callback);
   queue.queue_message(TestEvent{value});
   ASSERT_TRUE(event_received);
}