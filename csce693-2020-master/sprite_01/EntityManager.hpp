
#ifndef __EntityManager_HPP__
#define __EntityManager_HPP__

#include "Entity.hpp"

#include <vector>
#include <string>

class EntityManager
{
public:

   void clear_data();
   void update(const float dt);
   void render();
   bool has_no_entities() const;
   //added function for part 1
   void initialize();

   Entity& add_entity(const std::string name);
   std::vector<Entity*> get_entities() const;

   std::size_t get_entity_count() const;

   void list_all_entities() const;

private:
   std::vector<Entity*> entities;
};

#endif

