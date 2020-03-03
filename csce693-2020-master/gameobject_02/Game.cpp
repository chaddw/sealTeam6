
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"

#include "sdl_utils.hpp"
#include "gameobjects/Chopper.hpp"
#include "gameobjects/Tank.hpp"
#include "gameobjects/Pacman.hpp"
#include "sol/sol.hpp"

SDL_Renderer* Game::renderer{};
SDL_Window* Game::window{};

//declaring static variable
sol::state Game::lua;

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

   //open libraries
   lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
   //loads lua script file, throw exception if error occurs
   lua.script_file("config.lua");
   

}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}

void Game::load_level()
{
   /*//Original Code
   auto chopper = std::make_unique<Chopper>("../assets/images/chopper-single.png", 50.0f, 50.0f, 0.5f, 0.5f);
   auto tank = std::make_unique<Tank>("../assets/images/tank-big-down.png", 0.0f, 0.0f, 0.5f, 0.5f);
   auto pacman = std::make_unique<Pacman>("../assets/images/pacman/pacman_32x32.png", 100.0f, 100.0f, 0.5f, 0.5f);
   
   //game_objs.emplace_back(std::move(chopper));
   //game_objs.emplace_back(std::move(tank));
   //game_objs.emplace_back(std::move(pacman));
   */

   sol::table gameObjs = lua["gameobjs"];
   for (const auto& key_value_pair : gameObjs){
      sol::object player = key_value_pair.first;
      sol::table tbl = key_value_pair.second;

      bool validConfig = true;
      float xpos = 0;
      float ypos = 0;
      float xvel = 0;
      float yvel = 0;
      std::string kindType;

      std::cout << "loading " << player.as<std::string>() << std::endl;

      for (const auto& list : tbl){
         sol::type varType = list.second.get_type();


         switch (varType)
         {
            case sol::type::string:
               if (list.first.as<std::string>() == "kind")
               {
                  std::cout << "KIND: " << list.second.as<std::string>() << std::endl;
                  kindType = list.second.as<std::string>();
               }
               else{
                  std::cout << "Unkown string parameter read in lua config file" << std::endl;
                  validConfig = false;
               }
               break;
            
            case sol::type::number:
               if (list.first.as<std::string>() == "xpos")
               {
                  std::cout << "XPOS: " << list.second.as<std::string>() << std::endl;
                  xpos = list.second.as<float>();
               }
               else if (list.first.as<std::string>() == "ypos")
               {
                  std::cout << "YPOS: " << list.second.as<std::string>() << std::endl;
                  ypos = list.second.as<float>();
               }
               else if (list.first.as<std::string>() == "xvel")
               {
                  std::cout << "XVEL: " << list.second.as<std::string>() << std::endl;
                  xvel = list.second.as<float>();
               }
               else if (list.first.as<std::string>() == "yvel")
               {
                  std::cout << "YVEL: " << list.second.as<std::string>() << std::endl;
                  yvel = list.second.as<float>();
               }
               else{
                  std::cout << "Unkown number parameter read in lua config file" << std::endl;
                  validConfig = false;
               }
               break;
            
            default:
               std::cout << "Unkown type read in lua config file" << std::endl;
               validConfig = false;
               break;
         }
      }
      
      if (validConfig)
      {
         if (kindType == "chopper")
         {
            auto chopper = std::make_unique<Chopper>(xpos, ypos, xvel, yvel);
            game_objs.emplace_back(std::move(chopper));
         }
         else if (kindType == "tank")
         {
            auto tank = std::make_unique<Tank>(xpos, ypos, xvel, yvel);
            game_objs.emplace_back(std::move(tank));

         }
         else if (kindType == "pacman")
         {
            auto pacman = std::make_unique<Pacman>(xpos, ypos, xvel, yvel);
            game_objs.emplace_back(std::move(pacman));
         }
         else
         {
            std::cout << "unknown kind read from lua config file" << std::endl;
         }
      }
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
   for (auto& i: game_objs) {
      i->update(dt);
   }
}

void Game::render()
{
   SDL_RenderClear(renderer);
   for (auto& i: game_objs) {
      i->render();
   }
   SDL_RenderPresent(renderer);
}

