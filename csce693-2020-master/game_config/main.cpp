
#include "Game.hpp"
#include "lua.hpp"

#include <iostream>
#include <memory>

int main() {

   std::cout << "Creating game" << std::endl;

   // read Lua script to determine initial window size infomation
   lua_State* L = luaL_newstate();
   luaL_openlibs(L);

   //executes a lua file
   luaL_dofile(L, "config.lua");
   
   lua_getglobal(L, "xpos");
   int xpos = lua_tonumber(L, 1);
   lua_pop(L, 1);

   lua_getglobal(L, "ypos");
   int ypos = lua_tonumber(L, 1);
   lua_pop(L, 1);

   lua_getglobal(L, "width");
   int width = lua_tonumber(L, 1);
   lua_pop(L, 1);

   lua_getglobal(L, "height");
   int height = lua_tonumber(L, 1);
   lua_pop(L, 1);

   lua_getglobal(L, "fullscreen");
   bool fullscreen = lua_toboolean(L, 1);
   lua_pop(L, 1);

   std::cout << "xpos: " << xpos << std::endl;
   std::cout << "ypos: " << ypos << std::endl;
   std::cout << "width: " << width << std::endl;
   std::cout << "height: " << height << std::endl;
   std::cout << "height: " << fullscreen << std::endl;

   lua_close(L);

   //auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   auto game = std::make_unique<Game>("1st Game", xpos, ypos, width, height, fullscreen);

   
   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   return 0;
}

