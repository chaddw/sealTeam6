
#include <iostream>
#include <memory>

#include "Game.hpp"


int main() {

   //creates lua state with the help of sol and open libraries
   sol::state lua;
   lua.open_libraries(sol::lib::base);

   //loads scripts, exception is thrown by sol if error occurs with opening file
	bool fileError = lua.script_file("logic.lua");

   std::cout << "Creating game" << std::endl;
   auto game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      //lua stat is passed into update to access lua variables and functions
      game->update(lua);
      game->render();
   }

   return 0;
}

