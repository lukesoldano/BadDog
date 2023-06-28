#include "CollisionDetector.hpp"

using namespace Physics;

bool CollisionDetector::check(SDL_FRect object1, SDL_FRect object2) 
{ 
   if (object1.x <= object2.x)
   {
      if (object1.x + object1.w <= object2.x) return false;
   }
   else
   {
      if (object1.x >= object2.x + object2.w) return false;
   }

   // The x's are overlapping, check y
   if (object1.y <= object2.y)
   {
      if (object1.y + object1.h <= object2.y) return false;
   }
   else
   {
      if (object1.y >= object2.y + object2.h) return false;
   }

   return true;
}