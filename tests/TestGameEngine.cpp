#include <gtest/gtest.h>

#include "EventPublisher.hpp"
#include "EventTypes.hpp"
#include "GameEngine.hpp"
#include "GameState.hpp"

using namespace Game;

TEST(GameEngine, Singleton) 
{
   ASSERT_NE(nullptr, &Engine::instance());
}

TEST(GameEngine, InitializationAndTeardown) 
{
   auto& engine = Engine::instance();
   auto& state = State::instance();

   ASSERT_TRUE(engine.initialize());

   EXPECT_FALSE(state.m_quit_program);
   PUBLISH_EVENT(Events::QuitProgramRequested());
   EXPECT_TRUE(state.m_quit_program);

   ASSERT_TRUE(engine.teardown());
}