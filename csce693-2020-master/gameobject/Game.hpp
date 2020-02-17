
#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <memory>
#include <vector>

#include "SDL2/SDL.h"
#include "GameObject.hpp"
#include "Tank.hpp"
#include "Chopper.hpp"
#include "Pacman.hpp"

class Game {

public:
   Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
   ~Game();

   void load_level();

   void handle_events();
   void update(const float dt);
   void render();

   bool running()                { return is_running; }

   static SDL_Renderer* renderer;
   static SDL_Window* window;

   std::vector<std::unique_ptr<GameObject>> gameObjects;

private:
   int counter{};
   bool is_running{};
};

#endif

