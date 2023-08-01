#pragma once

#include <SDL_events.h>

namespace Events
{

struct QuitProgramRequested 
{
   SDL_QuitEvent m_sdl_event;
};

} // namespace Events