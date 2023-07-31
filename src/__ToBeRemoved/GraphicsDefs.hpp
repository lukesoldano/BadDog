#pragma once

#include "SDL_render.h"

#include <functional>

using RenderInstruction_t = std::function<bool(SDL_Renderer&)>;