// #pragma once

// #include <filesystem>
// #include <optional>

// // Forward declarations
// class SDL_Surface;

// namespace Graphics
// {

// // @warning This class is not thread safe
// class Surface
// {
//    SDL_Surface* m_sdl_surface = nullptr;

// public:

//    Surface() = delete;
//    Surface(const Surface&) = delete;
//    Surface(Surface&&);

//    virtual ~Surface();

//    Surface& operator=(const Surface&) = delete;
//    Surface& operator=(Surface&& rhs);

//    static std::optional<Surface> create_from_image(std::filesystem::path i_image_path);
   
//    // @warning Tear down any held surfaces before exiting the SDL for the sake of cleanliness
//    void teardown();

//    // @TODO I hate exposing this type directly, refactor this later - should only see this being
//    //       used in the Renderer class when creating textures
//    SDL_Surface* get_sdl_surface() const;

// private:

//    Surface(SDL_Surface* i_sdl_surface);

//    void teardown_internal();

// };

// } // namespace Window