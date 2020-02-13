
#include "Game.hpp"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono> 

int main() {
   std::unique_ptr<Game> game;
   std::cout << "Creating game" << std::endl;

   //Set delta time,  1/60 fps = 16666 microsecs
   std::chrono::microseconds deltaTime(16666);
   //std::chrono::microseconds deltaTime(33333);//testing on VM

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
      auto start = std::chrono::high_resolution_clock::now();

      //game functions
      game->handle_events();
      game->update();
      game->render();
      
      //gets end time
      auto end = std::chrono::high_resolution_clock::now();

      //calculates time in seconds
      auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start); 

      //checks if a delay is needed
      if (elapsedTime < deltaTime){
         //delays in MS
         std::this_thread::sleep_for(deltaTime-elapsedTime);
      }

      //testing: Prints time variable and FPS
      /*
      auto end2 = std::chrono::high_resolution_clock::now();
      auto elapsedTime2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start); 
      std::cout << "Delta: " << std::chrono::duration_cast<std::chrono::microseconds>(deltaTime).count() << ", ET: "<< std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count() << ", TET: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime2).count()  << "\n";
      std::cout << "FPS: " << 1/(std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime2).count()/1000000.0f) << std::endl;
      */
   }

   return 0;
}
