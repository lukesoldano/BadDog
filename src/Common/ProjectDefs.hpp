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
   int& m_x = SDL_Point::x;
   int& m_y = SDL_Point::y;

   Point() noexcept = default;
   Point(int i_x, int i_y) noexcept :
      SDL_Point{i_x, i_y} {}
   Point(const Point& i_other) noexcept :
      SDL_Point{i_other} {}
   Point(Point&& i_other) noexcept :
      SDL_Point{std::move(i_other)} {}
   virtual ~Point() noexcept = default;

   Point& operator=(const Point& i_other) noexcept 
   {
      SDL_Point::operator=(i_other);
      return *this;
   }

   Point& operator=(Point&& i_other) noexcept 
   {
      SDL_Point::operator=(std::move(i_other));
      return *this;
   }

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
   float& m_x = SDL_FPoint::x;
   float& m_y = SDL_FPoint::y;

   FPoint() noexcept = default;
   FPoint(float i_x, float i_y) noexcept :
      SDL_FPoint{i_x, i_y} {}
   FPoint(const FPoint& i_other) noexcept :
      SDL_FPoint{i_other} {}
   FPoint(FPoint&& i_other) noexcept :
      SDL_FPoint{std::move(i_other)} {}
   virtual ~FPoint() noexcept = default;

   FPoint& operator=(const FPoint& i_other) noexcept 
   {
      SDL_FPoint::operator=(i_other);
      return *this;
   }

   FPoint& operator=(FPoint&& i_other) noexcept 
   {
      SDL_FPoint::operator=(std::move(i_other));
      return *this;
   }

   inline Point to_point() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const FPoint& fPoint)
   {
      os << std::fixed << std::setw(6)
         << "FPoint : {x: " << fPoint.x 
         << ", y: " << fPoint.y << "}";
      return os;
   }

};

inline FPoint Point::to_fpoint() const { return FPoint{float(x), float(y)}; }
inline Point FPoint::to_point() const { return Point{std::lround(x), std::lround(y)}; }

struct Rect : public SDL_Rect
{
   int& m_x = SDL_Rect::x;
   int& m_y = SDL_Rect::y;
   int& m_w = SDL_Rect::w;
   int& m_h = SDL_Rect::h;

   Rect() noexcept = default;
   Rect(int i_x, int i_y, int i_w, int i_h) noexcept :
      SDL_Rect{i_x, i_y, i_w, i_h} {}
   Rect(const Rect& i_other) noexcept :
      SDL_Rect{i_other} {}
   Rect(Rect&& i_other) noexcept :
      SDL_Rect{std::move(i_other)} {}
   virtual ~Rect() noexcept = default;

   Rect& operator=(const Rect& i_other) noexcept
   {
      SDL_Rect::operator=(i_other);
      return *this;
   }

   Rect& operator=(Rect&& i_other) noexcept
   {
      SDL_Rect::operator=(std::move(i_other));
      return *this;
   }

   inline Point get_origin() const { return {x, y}; };

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
   float& m_x = SDL_FRect::x;
   float& m_y = SDL_FRect::y;
   float& m_w = SDL_FRect::w;
   float& m_h = SDL_FRect::h;

   FRect()  noexcept = default;
   FRect(float i_x, float i_y, float i_w, float i_h)  noexcept :
      SDL_FRect{i_x, i_y, i_w, i_h} {}
   FRect(const FRect& i_other)  noexcept :
      SDL_FRect{i_other} {}
   FRect(FRect&& i_other) noexcept :
      SDL_FRect{std::move(i_other)} {}
   virtual ~FRect()  noexcept = default;

   FRect& operator=(const FRect& i_other) noexcept 
   {
      SDL_FRect::operator=(i_other);
      return *this;
   }

   FRect& operator=(FRect&& i_other) noexcept 
   {
      SDL_FRect::operator=(std::move(i_other));
      return *this;
   }

   inline FPoint get_origin() const { return {x, y}; };

   inline Rect to_rect() const;
   inline std::string to_string() const { TO_STRING(); }

   friend std::ostream& operator<<(std::ostream& os, const FRect& frect)
   {
      os << std::fixed << std::setw(6)
         << "FRect : {x: " << frect.x 
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
// Asserts
#define ASSERT(message) \
   { \
      LOG_ERROR("ASSERT: '" << message); \
      assert(false && message); \
   }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Check macros
#define CHECK_CONDITION(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
   } 

#define CHECK_CONDITION_RETURN_VOID(condition) \
   if (!(condition)) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return; \
   } 

#define CHECK_CONDITION_RETURN_FALSE(condition) \
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
#define WATCH_VALUE_MESSAGE(value) { LogMessage(#value << " is: " << value); }
#define WATCH_VALUE_WARNING(value) { LogWarning(#value << " is: " << value); }
#define WATCH_VALUE_ERROR(value) { LogError(#value << " is: " << value); }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Development macros
#define NOT_IMPLEMENTED() \
   {\
      LOG_ERROR("Unimplemented code area hit!!!"); \
      assert(false && "Unimplemented code area hit!!!"); \
   }