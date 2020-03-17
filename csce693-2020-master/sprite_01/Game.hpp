
#ifndef __Game_HPP__
#define __Game_HPP__

#include "SDL2/SDL.h"
#include "sol/sol.hpp"

class AssetManager;

class Game
{
public:
   Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
   ~Game();

   void handle_events();
   void update(const float dt);
   void render();

   //added function for part 1
   void initialize();

   //static sol state variable
   static sol::state lua;

   void load_level(const int number);

   bool running()                { return is_running; }

   static SDL_Renderer* renderer;
   static AssetManager* asset_manager;

private:
   int counter{};
   bool is_running{};
   SDL_Window* window{};
};

#endif

