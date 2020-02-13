
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono> 

int main() {
   std::unique_ptr<Game> game;
   std::cout << "Creating game" << std::endl;

   //Set delta time, Demoninator = Frames per secs
   float deltaTime = 1.0f/(60.0f);

   //Tries to create game pointer, catches exception and exits if unable to
   try {
      game = std::make_unique<Game>("1st Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
   } catch(const char* ex) {
      std::cout << "Exception caught: " << ex << std::endl;
      exit(-1);
   }

   std::cout << "Starting game loop" << std::endl;
   while (game->running()) {
      //gets start time
      Uint64 start = SDL_GetPerformanceCounter();

      //game functions
      game->handle_events();
      game->update();
      game->render();
      
      //gets end time
      Uint64 end = SDL_GetPerformanceCounter();

      //calculates time in seconds
      float elapsedTime = (end-start)/static_cast<float>(SDL_GetPerformanceFrequency()); 

      //checks if a delay is needed
      if (elapsedTime < deltaTime){
         //delays in MS (hence 1000.0f)
	      SDL_Delay( floor((deltaTime - elapsedTime) * 1000.0f) );
      }

      //testing
      /*
      Uint64 end2 = SDL_GetPerformanceCounter();
      float elapsedTime2 = (end2-start)/(static_cast<float>(SDL_GetPerformanceFrequency())); 
      std::cout << "Delta: " << deltaTime * 1000 << ", ET: "<< elapsedTime * 1000 << ", TET: " << elapsedTime2 * 1000 << "\n";
      */
   }

   return 0;
}
