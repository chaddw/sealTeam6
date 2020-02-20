
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include "SDL2/SDL_image.h"

#include "texture_utils.hpp"
#include "GameObject.hpp"
#include "Tank.hpp"
#include "Chopper.hpp"
#include "Pacman.hpp"


SDL_Renderer* Game::renderer{};
SDL_Window* Game::window{};

//GameObject* tank{};
//GameObject* chopper{};
//GameObject* pacman{};

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   //delete tank;
   //delete chopper;
   //delete pacman;

   std::cout << "Game cleaned..." << std::endl;
}

void Game::load_level()
{
   /* // Original Code
   tank = new GameObject("../assets/images/tank-big-down.png", 0.0f, 0.0f, 0.5f, 0.5f);
   chopper = new GameObject("../assets/images/chopper-single.png", 50.0f, 50.0f, 0.5f, 0.5f);
   pacman = new GameObject("../assets/images/pacman/pacman_32x32.png", 100.0f, 100.0f, 0.5f, 0.5f);
   
   auto tank = std::make_unique<GameObject>( ../assets/images/tank-big-down.png", 0.0f, 0.0f, 0.5f, 0.5f);
   auto chopper = std::make_unique<GameObject>("../assets/images/chopper-single.png", 50.0f, 50.0f, 0.5f, 0.5f);
   auto pacman = std::make_unique<GameObject>("../assets/images/pacman/pacman_32x32.png", 100.0f, 100.0f, 0.5f, 0.5f);
   */   

   //Make each game object a unique pointer and place it in gameObjects

   try
   {
      auto tank = std::make_unique<Tank>( 0.0f, 0.0f, 0.5f, 0.5f);
      auto chopper = std::make_unique<Chopper>(50.0f, 50.0f, 0.5f, 0.5f);
      auto pacman = std::make_unique<Pacman>(100.0f, 100.0f, 0.5f, 0.5f);

      gameObjects.emplace_back(std::move(tank));
      gameObjects.emplace_back(std::move(chopper));
      gameObjects.emplace_back(std::move(pacman));
      
   } catch(const char* ex) 
   {
      std::cout << "Exception caught: " << ex << std::endl;
      exit(-1);
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

void Game::update(const float dt)
{
   /* //Old code
   tank->update(dt);
   chopper->update(dt);
   pacman->update(dt);
   */

   //For each gameObject update it
   for (auto& go : gameObjects){
      go->update(dt);
   }
}

void Game::render()
{
   SDL_RenderClear(renderer);
   /* //Old code
   tank->render();
   chopper->render();
   pacman->render();
   */

   //For each gameObject render it
   for (auto& go : gameObjects){
      go->render();
   }

   SDL_RenderPresent(renderer);
}

