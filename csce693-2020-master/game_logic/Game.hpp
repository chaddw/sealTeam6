
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "SDL2/SDL.h"
#include <sol/sol.hpp>

class Game {

public:
   Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
   ~Game();

   void handle_events();
   void update(sol::state &lua);
   //void update();

   void render();

   bool running()                { return is_running; }


private:
   bool is_running{};
   SDL_Window* window{};
   SDL_Renderer* renderer{};

};

#endif

