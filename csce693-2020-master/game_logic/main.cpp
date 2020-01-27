
#include "Game.hpp"

#include <iostream>
#include <memory>

int main() {

   sol::state lua;
   lua.open_libraries(sol::lib::base);
	lua.script_file("logic.lua");
 

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update(lua);
      game->render();
   }

   return 0;
}

