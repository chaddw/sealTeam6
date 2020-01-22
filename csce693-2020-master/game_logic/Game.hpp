
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "SDL2/SDL.h"

class Game {

public:
   Game() = default;
   ~Game() = default;

   void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
   void handle_events();
   void update();
   void render();
   void clean();

   bool running()            { return is_running; }

private:
   bool is_running{};
   SDL_Window* window{};
   SDL_Renderer* renderer{};
};


#endif
