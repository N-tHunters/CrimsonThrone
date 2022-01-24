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
  load_textures({"sword", "fire"});
  Location * open_world = new Location(4, 4, 100, 100, new FlatGenerator());
  location_map[0] = open_world;

  // Create City Center
  open_world->GetChunk(0, 0)->AddObj(create_wall(glm::vec3(200, 30, 200), glm::vec3(10, 60, 10), "fire"));
  open_world->GetChunk(0, 0)->AddActor(
  	new NPC(
  		"Totacres",
  		100,
  		new PhysicalObj(
  			new Mesh(
  				get_model("human"),
  				get_texture("fire")
  				),
  			true, true, false, false,
  			glm::vec3(10, 10, 10),
  			glm::vec3(0.0f),
  			"totacres",
  			get_model("human")->getBoundaryBox(1.0f)
  			)
  		)
  	);

  for(int i = 0; i < 100; i++) {
    open_world->GetChunk(0, 0)->AddObj(create_wall(glm::vec3(10 * (rand() % 40) + rand() % 10, 5, 10 * (rand() % 40) + rand() % 10), glm::vec3(10, 10, 10), GetDefaultTexture()));
  }

  SetCurrentLocation(open_world);
  open_world->LoadABS();
}
