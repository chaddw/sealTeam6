
#include "Game.hpp"
#include <iostream>
#include <sol/sol.hpp>

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
   //load lua file
   //sol::state Lua;
   //this->lua = &Lua;
   //lua.script_file("logic.lua");
   //this->lua = luaL_newstate();
	
	// load and execute from file
	//lua.script_file("logic.lua");
   //this->Lua->load("logic.lua");
   //lua.open_libraries(sol::lib::base);
   //open_libraries(sol::lib::base);
   //this->lua = inputState;

   //original code
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
   std::cout << "Game cleaned..." << std::endl;
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

void Game::update(sol::state &lua)
{
   //int count = 1;
   // call Lua's function update() to increment a counter
   // and print the returned value
   //sol::state lua;
	//lua.open_libraries(sol::lib::base);
	

	// load and execute from file
	//lua.script_file("logic.lua");
   //lua.load_file("logic.lua");
   //lua->load_file("logic.lua");

   //lua["count"] = 1;
   //sol::function up = Lua->get
   //sol::load_result luaUpdate = lua->load("count");
   //int count = luaUpdate();
   
   //count = lua.get<int>("count");
   sol::function fx = lua["update"];
   int count = fx();
   std::cout << count << std::endl;




}

void Game::render()
{
   SDL_RenderClear(renderer);
   // this is where we would add stuff to render
   SDL_RenderPresent(renderer);
}

