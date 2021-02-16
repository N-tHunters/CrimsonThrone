#include "worldmap.hpp"
#include <base/location/location.hpp>
#include <base/triggers/longjumptrigger.hpp>
#include <landscape/flatgenerator.hpp>
#include <landscape/dungeona1generator3d.hpp>
#include <unordered_map>

static std::unordered_map<int, Location *> location_map;

void init_demo_locations() {
  Location * open_world = new Location(10, 10, 10, 10, new FlatGenerator());
  location_map[0] = open_world;

  std::vector<std::tuple<Chunk *, glm::vec3>> exits;
  exits.push_back(std::make_tuple(open_world->GetChunk(0, 0), glm::vec3(2.0f, 2.0f, 2.0f)));

  for(int i = 1; i < 4; i++) {
    for(int j = 1; j < 4; j++) {
      location_map[1] = new Location(5, 5, 10, 10, new DungeonA1Generator3D(5, &exits));
      PhysicalObj * portal = new PhysicalObj(new Mesh("resources/textures/test.jpg", new Model("resources/models/portal.obj")),
					     false, true, false, false,
					     glm::vec3(5.f + 10.f * i, 3.f, 5.f + 10.f * j),
					     glm::vec3(0.0f, 0.0f, 0.0f),
					     "portal",
					     new BoundaryBox(1.0f, 1.0f, 1.0f));
      location_map[0]->GetChunk(i, j)->AddObj(portal);
      location_map[0]->GetChunk(i, j)->AddTrigger(new LongJumpTrigger(portal, glm::vec3(2.0f, 2.0f, 2.0f), location_map[1]->GetChunk(0, 0)));
    }
  }

  
  SetCurrentLocation(open_world);
}