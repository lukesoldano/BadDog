#pragma once

#include "Logger.hpp"

#include <assert.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper macros
#define TO_UINT_PTR(ptr) reinterpret_cast<std::uintptr_t>(ptr)

////////////////////////////////////////////////////////////////////////////////////////////////////
// Asserts
#define ASSERT(message) \
   { \
      LOG_ERROR("ASSERT: '" << message << "'"); \
      assert(false && std::string(message).c_str()); \
   }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Check macros - These macros will assert in Debug mode or otherwise log an error and return the 
//                specified type or not return at all if no type specified
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

#define CHECK_IF_POINTER_VALID_RETURN_FALSE(ptr) \
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
// Watch macros - These macros will log the value of the given variable
#define WATCH_VALUE(value) { LogMessage(#value << " is: " << value); }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Development macros
#define NOT_IMPLEMENTED() \
   {\
      LOG_ERROR("Unimplemented code area hit!!!"); \
      assert(false && "Unimplemented code area hit!!!"); \
   }