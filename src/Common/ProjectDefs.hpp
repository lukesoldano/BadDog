#pragma once

#include "Logger.hpp"

#include "SDL_rect.h"

#include <assert.h>
#include <cmath>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Value definitions
using EntityId = uint16_t;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Structs
//// Temporary shortening macros
#define TO_STRING() \
      std::ostringstream os; \
      os << *this; \
      return os.str();

//// Predeclarations
struct FPoint;
struct FRect;

//// Structs
struct Point : public SDL_Point
{
   inline FPoint to_fpoint() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const Point& point)
   {
      os << "Point : {x: " << point.x 
         << ", y: " << point.y << "}";
      return os;
   }

};

struct FPoint : public SDL_FPoint
{
   inline Point to_point() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const FPoint& fPoint)
   {
      os << "FPoint : {x: " << fPoint.x 
         << ", y: " << fPoint.y << "}";
      return os;
   }

};

inline FPoint Point::to_fpoint() const { return FPoint{float(x), float(y)}; }
inline Point FPoint::to_point() const { return Point{std::lround(x), std::lround(y)}; }

struct Rect : public SDL_Rect
{
   inline Point get_origin() { return {x, y}; };

   inline FRect to_frect() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const Rect& rect)
   {
      os << "Rect : {x: " << rect.x 
         << ", y: " << rect.y 
         << ", w: " << rect.w 
         << ", h: " << rect.h << "}";
      return os;
   }

};

struct FRect : public SDL_FRect
{
   inline FPoint get_origin() { return {x, y}; };

   inline Rect to_rect() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const FRect& frect)
   {
      os << "FRect : {x: " << frect.x 
         << ", y: " << frect.y 
         << ", w: " << frect.w 
         << ", h: " << frect.h << "}";
      return os;
   }

};

inline FRect Rect::to_frect() const { return FRect{float(x), float(y), float(w), float(h)}; }
inline Rect FRect::to_rect() const { return Rect{std::lround(x), std::lround(y), std::lround(w), std::lround(h)}; }

//// Undefine shorterning macros
#undef TO_STRING

////////////////////////////////////////////////////////////////////////////////////////////////////
// Check macros
#define CHECK_CONDITION(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
   } 

#define CHECK_CONDITION_RETURN_BOOL(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return false; \
   } 

#define CHECK_CONDITION_RETURN_NULLOPT(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return std::nullopt; \
   } 

#define CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return {}; \
   } 

#define CHECK_IF_POINTER_VALID(ptr) \
   if (nullptr == ptr) \
   { \
      LOG_ERROR("Given pointer '" << #ptr << "' is null!!!"); \
      assert(nullptr != ptr); \
   } 

#define CHECK_IF_POINTER_VALID_RETURN_BOOL(ptr) \
   if (nullptr == ptr) \
   { \
      LOG_ERROR("Given pointer '" << #ptr << "' is null!!!"); \
      assert(nullptr != ptr); \
      return false; \
   } 

#define CHECK_IF_POINTER_VALID_RETURN_NULLOPT(ptr) \
   if (nullptr == ptr) \
   { \
      LOG_ERROR("Given pointer '" << #ptr << "' is null!!!"); \
      assert(nullptr != ptr); \
      return std::nullopt; \
   } 

#define CHECK_IF_POINTER_VALID_RETURN_NULLPTR(ptr) \
   if (nullptr == ptr) \
   { \
      LOG_ERROR("Given pointer '" << #ptr << "' is null!!!"); \
      assert(nullptr != ptr); \
      return nullptr; \
   } 

////////////////////////////////////////////////////////////////////////////////////////////////////
// Watch macros
#define WATCH_VALUE_MESSAGE(value) LogMessage(#value << " is: " << value);
#define WATCH_VALUE_WARNING(value) LogWarning(#value << " is: " << value);
#define WATCH_VALUE_ERROR(value) LogError(#value << " is: " << value);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Development macros
#define NOT_IMPLEMENTED() \
   LOG_ERROR("Unimplemented code area hit!!!"); \
   assert(false && "Unimplemented code area hit!!!"); 