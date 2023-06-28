#pragma once

#include "Logger.hpp"

#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Concepts


////////////////////////////////////////////////////////////////////////////////////////////////////
// Check macros
#define CHECK_CONDITION(condition) \
   if (!condition) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
   } 

#define CHECK_CONDITION_RETURN_BOOL(condition) \
   if (!condition) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return false; \
   } 

#define CHECK_CONDITION_RETURN_NULLOPT(condition) \
   if (!condition) \
   { \
      LOG_ERROR("Failed condition '" << #condition << "' !!!"); \
      assert(false && #condition); \
      return std::nullopt; \
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