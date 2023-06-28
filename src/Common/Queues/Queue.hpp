#pragma once

#include <functional>

template <class MessageType>
class Queue
{
   std::function<void(const MessageType&)> m_message_handler;

public:

   Queue() = delete;
   Queue(std::function<void(const MessageType&)> i_message_handler) : 
      m_message_handler(i_message_handler) {}
   virtual ~Queue() = default;

   virtual void queue_message(const MessageType& i_message) = 0;

protected:

   void handle_message(const MessageType& i_message)
   {
      m_message_handler(i_message);
   }

};