#include <gtest/gtest.h>

#include "GameState.hpp"

using namespace Game;

TEST(GameState, Singleton) 
{
   ASSERT_NE(nullptr, &State::instance());
}