
#include "Game.hpp"
#include "lua.hpp"

#include <iostream>
#include <memory>

int main() {

   std::cout << "Creating game" << std::endl;

   //default values for SDL window creation
   int xpos = SDL_WINDOWPOS_CENTERED;
   int ypos = SDL_WINDOWPOS_CENTERED;
   int width = 800;
   int height = 600;
   bool fullscreen = false;

   //Lua state initialization
   lua_State* L = luaL_newstate();
   luaL_openlibs(L);

   //executes a lua file
   bool fileError = luaL_dofile(L, "config.lua");
   if (fileError)
   {
      std::cout << "error opening lua config file: using default values" <<std::endl;
   }
   else
   {
      //gets xpos variable from lua config file
      lua_getglobal(L, "xpos");
      //takes variable from lua stack and assigns to cpp variable
      xpos = lua_tonumber(L, 1);
      //pops the variable off the stack
      lua_pop(L, 1);

      //gets ypos variable from lua config file, assigns to cpp variable, & pops off stack
      lua_getglobal(L, "ypos");
      ypos = lua_tonumber(L, 1);
      lua_pop(L, 1);

      //gets width variable from lua config file, assigns to cpp variable, & pops off stack
      lua_getglobal(L, "width");
      width = lua_tonumber(L, 1);
      lua_pop(L, 1);

      //gets height variable from lua config file, assigns to cpp variable, & pops off stack
      lua_getglobal(L, "height");
      height = lua_tonumber(L, 1);
      lua_pop(L, 1);

      //gets fullscreen variable from lua config file, assigns to cpp variable, & pops off stack
      lua_getglobal(L, "fullscreen");
      fullscreen = lua_toboolean(L, 1);
      lua_pop(L, 1);
   }

   /*//testing
   std::cout << "xpos: " << xpos << std::endl;
   std::cout << "ypos: " << ypos << std::endl;
   std::cout << "width: " << width << std::endl;
   std::cout << "height: " << height << std::endl;
   std::cout << "fullscreen: " << fullscreen << std::endl;
   */

   //closes lua state
   lua_close(L);

   //original function
   //auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   //new function that takes parameters from lua config file
   auto game = std::make_unique<Game>("1st Game", xpos, ypos, width, height, fullscreen);
   

   
   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   return 0;
}

