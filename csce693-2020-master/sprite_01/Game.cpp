
#include "Game.hpp"

#include <iostream>
#include "SDL2/SDL_image.h"

#include "AssetManager.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "sol/sol.hpp"

SDL_Renderer* Game::renderer{};

EntityManager entity_mgr;
AssetManager* Game::asset_manager{new AssetManager()};

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

   load_level(1);
}

Game::~Game()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
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
   entity_mgr.update(dt);
}

void Game::render()
{
   SDL_RenderClear(renderer);
   entity_mgr.render();
   SDL_RenderPresent(renderer);
}

void Game::load_level(const int number)
{
   //load assets and entiities from lua stack
   sol::table assets = lua["assets"];
   sol::table entities = lua["entities"];

   std::cout << "Loading Assets: " << std::endl;

   //adds the assets
   for (const auto& key_value : assets)
   {
      sol::object assetName = key_value.first;
      sol::object fileName = key_value.second;

      std::string assetNameStr;
      std::string fileNameStr;

      //minor error checking to ensure parameters are the right type
      if (sol::type::string == assetName.get_type())
      {
         assetNameStr = assetName.as<std::string>();
         if (sol::type::string == fileName.get_type())
         {
            fileNameStr = fileName.as<std::string>();
            std::cout << "Asset name: " << assetNameStr << " file: " << fileNameStr << std::endl;
            asset_manager->add_texture(assetNameStr, fileNameStr.c_str());
         }
      }
   }

   //add entities
   for (const auto& key_value : entities)
   {
      sol::object entityName = key_value.first;
      sol::table tbl = key_value.second;

      std::string entityNameStr = entityName.as<std::string>();
      //variable containers for lua config file parameters
      bool validConfig = true;
      float xpos = 0;
      float ypos = 0;
      float xvel = 0;
      float yvel = 0;
      float width = 0;
      float height = 0;
      float scale = 0;
      std::string spriteId;


      //iterates through the lua paramenters for each component
      for (const auto& list : tbl){
         sol::object compName = list.first;
         std::cout << "loading " << compName.as<std::string>() << std::endl;
         sol::table listTable = list.second;

         for (const auto& subList : listTable){
            sol::type varType = subList.second.get_type();


            //checks the type and assigns it to the 
            switch (varType)
            {
               case sol::type::string:
                  if (subList.first.as<std::string>() == "texture_id")
                  {
                     std::cout << "Text Id: " << subList.second.as<std::string>() << std::endl;
                     spriteId = subList.second.as<std::string>();
                  }
                  else{
                     std::cout << "Unkown string parameter read in lua config file" << std::endl;
                     validConfig = false;
                  }
                  break;
               
               case sol::type::number:
                  if (subList.first.as<std::string>() == "position_x")
                  {
                     std::cout << "XPOS: " << subList.second.as<std::string>() << std::endl;
                     xpos = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "position_y")
                  {
                     std::cout << "YPOS: " << subList.second.as<std::string>() << std::endl;
                     ypos = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "velocity_x")
                  {
                     std::cout << "XVEL: " << subList.second.as<std::string>() << std::endl;
                     xvel = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "velocity_y")
                  {
                     std::cout << "YVEL: " << subList.second.as<std::string>() << std::endl;
                     yvel = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "width")
                  {
                     std::cout << "Width: " << subList.second.as<std::string>() << std::endl;
                     width = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "height")
                  {
                     std::cout << "Height: " << subList.second.as<std::string>() << std::endl;
                     height = subList.second.as<float>();
                  }
                  else if (subList.first.as<std::string>() == "scale")
                  {
                     std::cout << "Scale: " << subList.second.as<std::string>() << std::endl;
                     scale = subList.second.as<float>();
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
      }

      //checks if all parameter were correctly read before creating entity and 
      if (validConfig){
         std::cout << "Creating: " << entityNameStr << std::endl;
         Entity& general_entity(entity_mgr.add_entity(entityNameStr));
         general_entity.add_component<TransformComponent>(xpos,ypos,xvel,yvel,width,height,scale);
         general_entity.add_component<SpriteComponent>(spriteId);     
      }

   }

   /* Original Code
   // add assets to asset manager
   asset_manager->add_texture("tank-image", "../assets/images/tank-big-right.png");
   asset_manager->add_texture("chopper-image", "../assets/images/chopper-spritesheet.png");

   // create entities and add components to them
   Entity& tank_entity(entity_mgr.add_entity("tank"));
   tank_entity.add_component<TransformComponent>(0,0,20,20,32,32,1);
   tank_entity.add_component<SpriteComponent>("tank-image");

   Entity& chopper_entity(entity_mgr.add_entity("chopper"));
   chopper_entity.add_component<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
   chopper_entity.add_component<SpriteComponent>("chopper-image");
   */

   entity_mgr.list_all_entities();
}

void Game::initialize(){
   entity_mgr.initialize();
}