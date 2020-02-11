
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono> 

int main() {
   std::unique_ptr<Game> game;
   std::cout << "Creating game" << std::endl;
   //Uncomment line below to start keeping track of time
   //auto start = std::chrono::high_resolution_clock::now();
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
      //Uncomment both lines below to print time elapsed
      //auto end = std::chrono::high_resolution_clock::now();
      //std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << '\n';
      game->render();
      //Sleeps the thread for approximately 60hz
      std::this_thread::sleep_for(std::chrono::microseconds(16666));
   }

   return 0;
}
