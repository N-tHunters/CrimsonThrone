#include "worldmap.hpp"
#include <base/actors/npc.hpp>
#include <base/actors/npcai/wanderai.hpp>
#include <base/actors/npcai/humanlikeai.hpp>
#include <base/location/location.hpp>
#include <base/triggers/longjumptrigger.hpp>
#include <landscape/flatgenerator.hpp>
#include <landscape/overworldgenerator.hpp>
#include <landscape/dungeona1generator3d.hpp>
#include <unordered_map>
#include <render/models.hpp>
#include <render/textures.hpp>
#include <cstdlib>

std::unordered_map<int, Location *> location_map;

void init_demo_locations() {
  Location * open_world = new Location(100, 100, 100, 100, new OverWorldGenerator());
  location_map[0] = open_world;

  /*std::vector<std::tuple<Chunk *, glm::vec3>> exits;
    exits.push_back(std::make_tuple(open_world->GetChunk(0, 0), glm::vec3(2.0f, 2.0f, 2.0f)));

    Model* portal_model = new Model("resources/models/portal.obj");

    for(int i = 1; i < 4; i++) {
    for(int j = 1; j < 4; j++) {
    location_map[(i - 1) * 4 + j] = new Location(5, 5, 10, 10, new DungeonA1Generator3D(5, &exits));
    PhysicalObj * portal = new PhysicalObj(new Mesh("resources/textures/test.jpg", portal_model),
    false, true, false, false,
    glm::vec3(5.f + 10.f * i, 3.f, 5.f + 10.f * j),
    glm::vec3(0.0f, 0.0f, 0.0f),
    "portal",
    new BoundaryBox(1.0f, 1.0f, 1.0f));
    location_map[0]->GetChunk(i, j)->AddObj(portal);
    location_map[0]->GetChunk(i, j)->AddTrigger(new LongJumpTrigger(portal, glm::vec3(2.0f, 2.0f, 2.0f), location_map[(i - 1) * 4 + j]->GetChunk(0, 0)));
    }
    }*/

  for(int i = 0; i < rand() % 10; i++){
    Actor * test_actor = (Actor *)new NPC("totacres", 10,
					  new PhysicalObj(new Mesh(get_model("human"), get_texture("icon")),
							  true, true, false, false, glm::vec3(rand() % 10, rand() % 10 + 10, rand() % 10), glm::vec3(3.0f, 1.0f, 1.0f), "test_actor_po",
							  get_model("human")->getBoundaryBox(1.0f)),
					  (NPCAI *)new HumanlikeAI());
    open_world->GetChunk(0, 0)->AddActor(test_actor);
  }

  
  for(int i = 0; i < rand() % 10; i++){
    Item * test_item = (Item *)new Item("totacres",
					  new PhysicalObj(new Mesh(get_model("human"), get_texture("icon")),
							  true, true, false, false, glm::vec3(rand() % 10, rand() % 10 + 10, rand() % 10), glm::vec3(3.0f, 1.0f, 1.0f), "test_item_po",
							  get_model("human")->getBoundaryBox(1.0f)));
    open_world->GetChunk(0, 0)->AddItem(test_item);
  }

  SetCurrentLocation(open_world);
  open_world->LoadABS();
}
