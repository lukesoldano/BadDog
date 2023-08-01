#pragma once

class EntityIdManager
{
public:

   EntityIdManager(const EntityIdManager&) = delete;
   EntityIdManager(EntityIdManager&&) = delete;

   EntityIdManager& operator=(const EntityIdManager&) = delete;
   EntityIdManager& operator=(EntityIdManager&&) = delete;

   inline static EntityIdManager& instance()
   {
      static EntityIdManager manager;
      return manager;
   }

private:

   EntityIdManager() = default;
   virtual ~EntityIdManager() = default;

};