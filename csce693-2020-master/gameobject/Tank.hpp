
#ifndef __TANK_HPP__
#define __TANK_HPP__

#include "GameObject.hpp"

#include "SDL2/SDL.h"

class Tank : public GameObject {
public:
   Tank(const char* filename_img,
              const float xpos, const float ypos,
              const float xvel, const float yvel);

   Tank(const float xpos, const float ypos,
              const float xvel, const float yvel);
              
   virtual ~Tank();

   virtual void update(const float dt);
   virtual void render();

private:
   float xpos{}, ypos{};
   float xvel{}, yvel{};

   SDL_Texture* texture{};
   SDL_Rect src_rect, dest_rect;
};

#endif

