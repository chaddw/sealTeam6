
#ifndef __PACMAN_HPP__
#define __PACMAN_HPP__

#include "GameObject.hpp"

#include "SDL2/SDL.h"

class Pacman : public GameObject {
public:
   //Overload init functions to allow for new image or default
   Pacman(const char* filename_img,
              const float xpos, const float ypos,
              const float xvel, const float yvel);

   Pacman(const float xpos, const float ypos,
              const float xvel, const float yvel);
              
   ~Pacman();

   virtual void update(const float dt);
   virtual void render();

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture{};
   SDL_Rect src_rect, dest_rect;
};

#endif

