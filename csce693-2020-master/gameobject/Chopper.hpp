
#ifndef __CHOPPER_HPP__
#define __CHOPPER_HPP__

#include "GameObject.hpp"

#include "SDL2/SDL.h"

class Chopper : public GameObject {
public:
   //Overload init functions to allow for new image or default
   Chopper(const char* filename_img,
              const float xpos, const float ypos,
              const float xvel, const float yvel);

   Chopper(const float xpos, const float ypos,
              const float xvel, const float yvel);
              
   virtual ~Chopper();

   virtual void update(const float dt);
   virtual void render();

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture{};
   SDL_Rect src_rect, dest_rect;
};

#endif

