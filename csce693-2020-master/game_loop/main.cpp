
#include "Game.hpp"

#include <iostream>
#include <memory>

int main() {
   std::unique_ptr<Game> game;
   std::cout << "Creating game" << std::endl;
   
   //Tries to create game pointer, catches exception and exits if unable to
   try {
      game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   } catch(const char* ex) {
      std::cout << "Exception caught: " << ex << std::endl;
      exit(-1);
   }

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      game->handle_events();
      game->update();
      game->render();
   }

   return 0;
}
