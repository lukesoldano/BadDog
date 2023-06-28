#pragma once

#include "Camera.hpp"
#include "GraphicsDefs.hpp"
#include "Logger.hpp"
#include "ProjectDefs.hpp"
#include "StaticEntity.hpp"

namespace Graphics
{

namespace RenderInstructionFactory
{
   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Declarations
   inline RenderInstruction_t get_instruction(SDL_Point i_xy_1, SDL_Point i_xy_2);
   inline RenderInstruction_t get_instruction(SDL_FPoint i_xy_1, SDL_FPoint i_xy_2);
   inline RenderInstruction_t get_instruction(Rect i_rectangle);
   inline RenderInstruction_t get_instruction(FRect i_rectangle);
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              std::optional<Rect> i_render_clip,
                                              std::optional<Rect> i_render_quad = std::nullopt,
                                              float i_rotation_angle = 0.0f,
                                              SDL_RendererFlip i_flip = SDL_FLIP_NONE);
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              std::optional<Rect> i_render_clip,
                                              std::optional<FRect> i_render_quad = std::nullopt,
                                              float i_rotation_angle = 0.0f,
                                              SDL_RendererFlip i_flip = SDL_FLIP_NONE);

   inline RenderInstruction_t get_static_entity_instruction(const CameraFrame& i_camera_frame,
                                                            const Game::StaticEntity& i_entity);

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
   inline RenderInstruction_t get_instruction(Rect i_rectangle)
   {
      return [rect = std::move(i_rectangle)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderFillRect(&i_renderer, &rect))
         {
            LOG_ERROR("Failed to render " << rect << ", SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering a float specified fill rectangle (the current draw color will be used)
   inline RenderInstruction_t get_instruction(FRect i_rectangle)
   {
      return [rect = std::move(i_rectangle)](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderFillRectF(&i_renderer, &rect))
         {
            LOG_ERROR("Failed to render " << rect << ", SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering any specific portion of a texture
   // @param[in] i_render_clip determines what quadrant of the texture you want to render -
   //            entire texture is rendered if nullopt is provided
   // @param[in] i_render_quad determines what quadrant of the surface you want to render this
   //            texture quadrant to - entire surface allowed if nullopt is provided
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              std::optional<Rect> i_render_clip,
                                              std::optional<Rect> i_render_quad,
                                              float i_rotation_angle,
                                              SDL_RendererFlip i_flip)
   {
      return [&texture = i_texture, 
              render_clip = std::move(i_render_clip),
              render_quad = std::move(i_render_quad),
              rotation_angle = i_rotation_angle,
              flip = i_flip](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderCopyEx(&i_renderer, 
                                   texture.get_sdl_texture(), 
                                   render_clip.has_value() ? &render_clip.value() : nullptr, 
                                   render_quad.has_value() ? &render_quad.value() : nullptr,
                                   rotation_angle,
                                   nullptr,
                                   flip))
         {
            LOG_ERROR("Failed to render texture, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   // For rendering any specific portion of a texture (float-based)
   // For rendering any specific portion of a texture
   // @param[in] i_render_clip determines what quadrant of the texture you want to render -
   //            entire texture is rendered if nullopt is provided
   // @param[in] i_render_quad determines what quadrant of the surface you want to render this
   //            texture quadrant to - entire surface allowed if nullopt is provided
   inline RenderInstruction_t get_instruction(const Texture& i_texture,
                                              std::optional<Rect> i_render_clip,
                                              std::optional<FRect> i_render_quad,
                                              float i_rotation_angle,
                                              SDL_RendererFlip i_flip)
   {
      return [&texture = i_texture, 
              render_clip = std::move(i_render_clip),
              render_quad = std::move(i_render_quad),
              rotation_angle = i_rotation_angle,
              flip = i_flip](SDL_Renderer& i_renderer)
      {
         if (0 != SDL_RenderCopyExF(&i_renderer, 
                                    texture.get_sdl_texture(), 
                                    render_clip.has_value() ? &render_clip.value() : nullptr,
                                    render_quad.has_value() ? &render_quad.value() : nullptr,
                                    rotation_angle,
                                    nullptr,
                                    flip))
         {
            LOG_ERROR("Failed to render f-texture, SDL Error: " << SDL_GetError());
            return false;
         }
         return true;
      };
   }

   inline RenderInstruction_t get_static_entity_instruction(const CameraFrame& i_camera_frame,
                                                            const Game::StaticEntity& i_entity)
   {
      if (std::holds_alternative<Game::FRectBarrier>(i_entity.m_data))
      {
         const auto& barrier = std::get<Game::FRectBarrier>(i_entity.m_data);
         FRect barrier_frect = std::get<Game::FRectBarrier>(i_entity.m_data);
         barrier_frect.x -= i_camera_frame.m_level_position.x;
         barrier_frect.y -= i_camera_frame.m_level_position.y;

         // renderer.set_draw_color(i_entity.m_rgba_color);
         return [color = barrier.m_rgba_color, barrier_frect = std::move(barrier_frect)](SDL_Renderer& i_renderer)
         {
            if (0 != SDL_SetRenderDrawColor(&i_renderer, 
                                            color.m_r, 
                                            color.m_g, 
                                            color.m_b, 
                                            color.m_a))
            {
               LOG_WARNING("Failed to set draw color, SDL Error: " << SDL_GetError());
               return false;
            }

            if (0 != SDL_RenderFillRectF(&i_renderer, &barrier_frect))
            {
               LOG_ERROR("Failed to render " << barrier_frect << ", SDL Error: " << SDL_GetError());
               return false;
            }
            return true;
         };
      }
      else
      {
         return RenderInstruction_t();
      }
   }

} // RenderInstructionFactory

} // Graphics