#include "flatchunkloader.hpp"
#include <landscape/landscapegenerator.hpp>
#include <base/actors/npc.hpp>

FlatChunkLoader::FlatChunkLoader(float size, int vertices_number, glm::vec3 position) {
  this->size = size;
  this->vertices_number = vertices_number;
  this->position = position;
  this->house = false;
}

void FlatChunkLoader::Load(AbstractChunk * chunk) {
  std::vector<std::vector<float>> * height_map = new std::vector<std::vector<float>>();
  std::vector<float> v;

  for (int i = 0; i < vertices_number; i ++) {
    v.clear();
    for (int j = 0; j < vertices_number; j ++) {
      v.push_back(0.0f);
    }
    height_map->push_back(v);
  }

  std::vector<unsigned char> pixels;

  for (int i = 0; i < 32; i ++ ) {
    for (int j = 0; j < 32; j ++) {
      pixels.push_back(0);
      pixels.push_back(0);
      pixels.push_back(0);
    }
  }

  // GLuint blend_texture = createTexture(pixels, 32);

  GLuint texture1 = get_texture("grass");
  GLuint texture2 = get_texture("grass");

  LoadEnd(height_map, chunk, texture1, texture2, pixels);
}

void FlatChunkLoader::LoadObjects(AbstractChunk* chunk) {
  if (rand() % 10 < 3) {
    chunk->AddObj(create_wall(glm::vec3(chunk->GetX() * 100.0f + 50.0f, 5.0f, chunk->GetY() * 100.0f + 50.0f), glm::vec3(10, 10, 10), "stone"));
    chunk->AddActor(
  	new NPC(
  		"Totacres",
  		100,
  		new PhysicalObj(
  			new Mesh(
  				get_model("human"),
  				get_texture("fire")
  				),
  			true, true, false, false,
  			glm::vec3(chunk->GetX() * 100.0f + 50.0f, 10.0f, chunk->GetY() * 100.0f + 61.0f),
  			glm::vec3(0.0f),
  			"totacres",
  			get_model("human")->getBoundaryBox(1.0f)
  			)
  		)
  	);

  }
  this->house = true;
}


bool FlatChunkLoader::AreObjectsLoaded() {
  return this->house;
}
