#pragma once

#include "Queue.hpp"

template <class MessageType>
class ImmediateQueue : public Queue<MessageType>
{
public:

   ImmediateQueue() = delete;
   ImmediateQueue(std::function<void(const MessageType&)> i_message_handler) : 
      Queue<MessageType>(i_message_handler) {}
   virtual ~ImmediateQueue() = default;

   void queue_message(const MessageType& i_message) override 
   { 
      Queue<MessageType>::handle_message(i_message); 
   }

};