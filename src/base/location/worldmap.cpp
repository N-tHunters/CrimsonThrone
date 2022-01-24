#include "worldmap.hpp"
#include <base/actors/npc.hpp>
#include <base/actors/npcai/aggressivewandererai.hpp>
#include <base/actors/npcai/humanlikeai.hpp>
#include <base/location/location.hpp>
#include <base/triggers/longjumptrigger.hpp>
#include <base/items/weapon.hpp>
#include <physics/boundary.hpp>
#include <landscape/flatgenerator.hpp>
#include <landscape/overworldgenerator.hpp>
#include <landscape/dungeona1generator3d.hpp>
#include <landscape/landscapegenerator.hpp>
#include <unordered_map>
#include <render/models.hpp>
#include <render/textures.hpp>
#include <cstdlib>

std::unordered_map<int, Location *> location_map;

void init_demo_locations() {
  load_textures({"sword", "wood"});
  Location * open_world = new Location(4, 4, 100, 100, new FlatGenerator());
  location_map[0] = open_world;

  std::vector<glm::vec4>roads;

  roads.push_back(glm::vec4(2.5f, 1.0f, 5.0f, 2.0f));


  for(auto road: roads)
    open_world->GetChunk(0, 0)->AddObj(create_wall(glm::vec3(road.x, 0, road.y), glm::vec3(road.z, 0.1f, road.w), "wood"));

  SetCurrentLocation(open_world);
  open_world->LoadABS();
}
