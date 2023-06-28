#pragma once

#include "CommonDefs.hpp"
#include "GraphicsDefs.hpp"
#include "Logger.hpp"

#include "SDL_rect.h"

namespace Graphics
{

namespace RenderInstructionFactory
{
   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Declarations
   inline RenderInstruction_t get_instruction(SDL_Point i_xy_1, SDL_Point i_xy_2);
   inline RenderInstruction_t get_instruction(SDL_FPoint i_xy_1, SDL_FPoint i_xy_2);
   inline RenderInstruction_t get_instruction(SDL_Rect i_rectangle);
   inline RenderInstruction_t get_instruction(SDL_FRect i_rectangle);
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              SDL_Rect i_render_clip,
                                              std::optional<SDL_Rect> i_render_quad = std::nullopt);

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Definitions

   // For rendering an int specified line (the current draw color will be used)
   inline RenderInstruction_t get_instruction(SDL_Point i_xy_1, SDL_Point i_xy_2)
   {
      return [xy_1 = std::move(i_xy_1), xy_2 = std::move(i_xy_2)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderDrawLine(&i_renderer, xy_1.x, xy_1.y, xy_2.x, xy_2.y))
         {
            LOG_ERROR("Failed to render line, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering a float specified line (the current draw color will be used)
   inline RenderInstruction_t get_instruction(SDL_FPoint i_xy_1, SDL_FPoint i_xy_2)
   {
      return [xy_1 = std::move(i_xy_1), xy_2 = std::move(i_xy_2)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderDrawLineF(&i_renderer, xy_1.x, xy_1.y, xy_2.x, xy_2.y))
         {
            LOG_ERROR("Failed to render f-line, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering an int specified fill rectangle (the current draw color will be used)
   inline RenderInstruction_t get_instruction(SDL_Rect i_rectangle)
   {
      return [rect = std::move(i_rectangle)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderFillRect(&i_renderer, &rect))
         {
            LOG_ERROR("Failed to render rect, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering a float specified fill rectangle (the current draw color will be used)
   inline RenderInstruction_t get_instruction(SDL_FRect i_rectangle)
   {
      return [rect = std::move(i_rectangle)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderFillRectF(&i_renderer, &rect))
         {
            LOG_ERROR("Failed to render f-rect, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering any specific portion of a texture
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              SDL_Rect i_render_clip,
                                              std::optional<SDL_Rect> i_render_quad)
   {
      return [&texture = i_texture, 
              render_clip = std::move(i_render_clip),
              render_quad = std::move(i_render_quad)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderCopy(&i_renderer, 
                                 texture.get_sdl_texture(), 
                                 &render_clip, 
                                 render_quad.has_value() ? &render_quad.value() : nullptr))
         {
            LOG_ERROR("Failed to render texture, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

} // RenderInstructionFactory

} // Graphics