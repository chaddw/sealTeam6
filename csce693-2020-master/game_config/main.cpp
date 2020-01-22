
#include "Game.hpp"

#include <iostream>

int main() {

   std::cout << "Creating game" << std::endl;
   Game* game = new Game();

   // use the configuration info available in the config.lua script
   game->init("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   game->clean();
   return 0;
}

