
#include "Game.hpp"
#include <iostream>

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   Uint32 flags{};
   if (fullscreen) {
      flags = SDL_WINDOW_FULLSCREEN;
   }

   if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
      std::cout << "Subsystems initialized..." << std::endl;
      window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
      if (window) {
         std::cout << "Window created..." << std::endl;
      }
      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer) {
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
         std::cout << "Renderer created..." << std::endl;
      }
      is_running = true;
   } else {
      is_running = false;
   }
}

void Game::handle_events()
{
   SDL_Event event;
   SDL_PollEvent(&event);
   switch (event.type) {
      case SDL_QUIT:
         is_running = false;
         break;
      default:
         break;
   }
}

void Game::update()
{
   // call Lua's function update() to increment a counter
   // and print the returned value
}

void Game::render()
{
   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);
}

void Game::clean()
{
   SDL_DestroyRenderer(renderer);
   // this is where we would add stuff to render
   SDL_DestroyWindow(window);
   std::cout << "Game cleaned..." << std::endl;
}



