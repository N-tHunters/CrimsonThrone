#include "dungeona1generator3d.hpp"
#include <base/location/location.hpp>
#include <utility>
#include <base/configuration.hpp>
#include <base/triggers/longjumptrigger.hpp>

const float wall_height = 6.0f;
const float wall_width = 0.5f;
const int step_count = 10;

DungeonA1Generator3D::DungeonA1Generator3D(size_t floors) : DungeonGenerator(floors) {
  this->exits = nullptr;
}
DungeonA1Generator3D::DungeonA1Generator3D(size_t floors, std::vector<std::tuple<Chunk *, glm::vec3>> * exits) : DungeonGenerator(floors) {
  this->exits = exits;
}


void DungeonA1Generator3D::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  FlatGenerator::Generate(location, width, height, chunk_width, chunk_height, vertices_number);
  GetDefaultTexture() = GetDefaultTexture();
  used.clear();
  for (size_t i = 0; i < width * height * floors; i++)
    used.push_back(false);

  walls.clear();
  for (size_t i = 0; i < (height + width * (height * 2 + 1) + width * height) * floors; i ++)
    walls.push_back(true);

  Model* portal_model = new Model("resources/models/portal.obj");

  ladders.clear();
  for (size_t i = 0; i < width * height * floors; i++)
    ladders.push_back(NO_LADDER);

  GenerateDungeon(0, 0, 0, width, height, floors);

  // PrintDungeon3D(height, width, floors);

  for(size_t z = 0; z < floors; z++) {
    for(size_t i = 0; i < width + 1; i ++) {
      for(size_t j = 0; j < height; j ++) {
	if(walls[UP_WALL_3D(i, j, z)]) { 
	  if(i == width)
	    location->GetChunk(width - 1, j)
	      ->AddObj(create_wall(glm::vec3(chunk_width * i - 0.5f,
					     wall_height * 0.5f + wall_height * z,
					     chunk_height * 0.5f + chunk_height * j),
				   glm::vec3(wall_width,
					     wall_height,
					     chunk_height),
				   GetDefaultTexture()));
	  else
	    location->GetChunk(i, j)
	      ->AddObj(create_wall(glm::vec3(chunk_width * i,
					     wall_height * 0.5f + wall_height * z,
					     chunk_height * 0.5f + chunk_height * j),
				   glm::vec3(wall_width,
					     wall_height,
					     chunk_height),
				   GetDefaultTexture()));
	}
      }
    }
  }

  for(size_t z = 0; z < floors; z++) {
    for(size_t i = 0; i < height + 1; i ++) {
      for(size_t j = 0; j < width; j ++) {
	if(walls[RIGHT_WALL_3D(j, i, z)]) {
	  if(i == height)
	    location->GetChunk(j, height - 1)
	      ->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j,
					     wall_height * 0.5f + wall_height * z,
					     chunk_height * i - 0.3f),
				   glm::vec3(chunk_width,
					     wall_height,
					     wall_width),
				   GetDefaultTexture()));
	  else
	    location->GetChunk(j, i)
	      ->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j,
					     wall_height * 0.5f + wall_height * z,
					     chunk_height * i - 0.3f),
				   glm::vec3(chunk_width,
					     wall_height,
					     wall_width),
				   GetDefaultTexture()));
	}
      }
    }
  }

  for (size_t z = 0; z < floors; z ++) {
    for (size_t i = 0; i < height; i ++) {
      for (size_t j = 0; j < width; j ++) {
	if(walls[ROOF_3D(j, i, z)])
	  location->GetChunk(j, i)
	    ->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j,
					   wall_height + wall_height * z - wall_width * 0.5 + 0.05f,
					   chunk_height * i + 0.5f * chunk_height),
				 glm::vec3(chunk_width,
					   wall_width,
					   chunk_height),
				 GetDefaultTexture()));
      }
    }
  }

  float step_size = chunk_width * 0.5f / (float)step_count;

  // Ladders
  for (size_t z = 0; z < floors; z ++) {
    for (size_t i = 0; i < height; i ++) {
      for (size_t j = 0; j < width; j ++) {
	if(ladders[z * width * height + i * width + j] == LADDER_BACKWARD) {
	  for(short unsigned int k = 1; k < step_count; k++) {
	    location->GetChunk(j, i)
	      ->AddObj(create_wall(glm::vec3(chunk_width * j + chunk_width - wall_height + step_size * k,
					     wall_height * z + step_size * k - wall_height * 0.1,
					     chunk_height * i + 0.5f * chunk_height),
				   glm::vec3(step_size,
					     step_size,
					     chunk_height),
				   GetDefaultTexture()));
	    
	  }
	} else if(ladders[z * width * height + i * width + j] == LADDER_FORWARD) {
	  for(short unsigned int k = 1; k < step_count; k++) {
	    location->GetChunk(j, i)
	      ->AddObj(create_wall(glm::vec3(chunk_width * j + chunk_width * 0.5 - step_size * k,
					     wall_height * z + step_size * k - wall_height * 0.1,
					     chunk_height * i + 0.5f * chunk_height),
				   glm::vec3(step_size,
					     step_size,
					     chunk_height),
				   GetDefaultTexture()));
	    
	  }
	} else if(ladders[z * width * height + i * width + j] == LADDER_LEFT) {
	  for(short unsigned int k = 1; k < step_count; k++) {
	    location->GetChunk(j, i)
	      ->AddObj(create_wall(glm::vec3(chunk_width * j + chunk_width * 0.5,
					     wall_height * z + step_size * k - wall_height * 0.1,
					     chunk_height * i + 0.5f * chunk_height + step_size * k),
				   glm::vec3(chunk_width,
					     step_size,
					     step_size),
				   GetDefaultTexture()));
	    
	  }
	} else if(ladders[z * width * height + i * width + j] == LADDER_RIGHT) {
	  for(short unsigned int k = 1; k < step_count; k++) {
	    location->GetChunk(j, i)
	      ->AddObj(create_wall(glm::vec3(chunk_width * j + chunk_width * 0.5,
					     wall_height * z + step_size * k - wall_height * 0.1,
					     chunk_height * i + 0.5f * chunk_height - step_size * k),
				   glm::vec3(chunk_width,
					     step_size,
					     step_size),
				   GetDefaultTexture()));
	    
	  }
	}
      }
    }
  }


  if(exits == nullptr) return;

  // Generate exits
  std::vector<std::tuple<int, int, int>> visited_cells;
  for(size_t z = 0; z < floors; z++) {
    for(size_t i = 0; i < width; i++) {
      for(size_t j = 0; j < height; j++) {
	if(used[z * width * height + j * width + i])
	  visited_cells.push_back({i, j, z});
      }
    }
  }

  for(int i = 0; i < exits->size(); i++) {
    int choice = rand() % visited_cells.size();
    
    std::tuple<int, int, int> coords = visited_cells[choice];
    printf("%d %d %d\n", std::get<0>(coords), std::get<1>(coords), std::get<2>(coords));

    PhysicalObj * portal = new PhysicalObj(new Mesh("resources/textures/fire.png", portal_model),
					   false, true, false, false,
					   glm::vec3(chunk_width * 0.5f + chunk_width * std::get<0>(coords), 3.f + wall_height * std::get<2>(coords), chunk_height * 0.5f + chunk_height * std::get<1>(coords)),
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   "portal",
					   new BoundaryBox(1.0f, 1.0f, 1.0f));
    location->GetChunk(0, 0)->AddObj(portal);
    Chunk * chunk = location->GetChunkByPosition(portal->getPosition().x, portal->getPosition().z);
    chunk->AddTrigger(new LongJumpTrigger(portal, std::get<1>(exits->at(i)), std::get<0>(exits->at(i))));

    visited_cells.erase(choice + visited_cells.begin());
  }
}

void DungeonA1Generator3D::GenerateDungeon(int tx, int ty, int tz, int width, int height, int floors) {
  used[tz * width * height + ty * width + tx] = true;
  std::vector<std::tuple<int, int, int>> choices;
  bool side = false;
  bool zmov = false;
  
  do {
    choices.clear();
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
	if (abs(i + j) != 1) continue;
	int nx = tx + i;
	int ny = ty + j;
	int nz = tz;
	if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;
	// Floor movements
	if (!used[nz * width * height + ny * width + nx] && !zmov)
	  choices.push_back({nx, ny, nz});
      }
    }
    if (!side && !zmov) {
      int nx, ny, nz;
      bool found = true;
      if(!walls[UP_WALL_3D(tx, ty, tz)] && tx + 1 < width) { nx = tx + 1; ny = ty; }
      else if(!walls[DOWN_WALL_3D(tx, ty, tz)] && tx - 1 >= 0) { nx = tx - 1; ny = ty; }
      else if(!walls[LEFT_WALL_3D(tx, ty, tz)] && ty - 1 >= 0) { nx = tx; ny = ty - 1; }
      else if(!walls[RIGHT_WALL_3D(tx, ty, tz)] && ty + 1 < height) { nx = tx; ny = ty + 1; }
      else found = false;

      if(found) {
	// Go up
	if(tz != floors - 1 && walls[ROOF_3D(tx, ty, tz)]) {
	  nz = tz + 1;
	  if (!used[nz * width * height + ny * width + nx] &&
	      !used[nz * width * height + ty * width + tx])
	    choices.push_back({nx, ny, nz});
	}
	// Go down
	if(tz != 0 && walls[FLOOR_3D(tx, ty, tz)]) {
	  nz = tz - 1;
	  if (!used[nz * width * height + ny * width + nx] &&
	      !used[nz * width * height + ty * width + tx])
	    choices.push_back({nx, ny, nz});
	}
      }
    }
    if (choices.size() == 0) break;

    int choice = rand() % choices.size();
    int nx = std::get<0>(choices[choice]);
    int ny = std::get<1>(choices[choice]);
    int nz = std::get<2>(choices[choice]);

    int dy = ny - ty;
    int dx = nx - tx;
    int dz = nz - tz;

    if (dz == 0) {
      side = true;
      if (dy != 0) {
	if (dy == -1) {
	  walls[RIGHT_WALL_3D(tx, ty, tz)] = false;
 	} else {
	  walls[LEFT_WALL_3D(tx, ty, tz)] = false;
	}
      } else {
	if (dx == -1) {
	  walls[UP_WALL_3D(tx, ty, tz)] = false;
	} else {
	  walls[DOWN_WALL_3D(tx, ty, tz)] = false;
	}
      }
    } else {
      zmov = true;
      int ladder = NO_LADDER;
      if (dy != 0) {
	if (dy == -1) {
	  ladder = LADDER_RIGHT;
	  walls[RIGHT_WALL_3D(tx, ty, nz)] = false;
 	} else {
	  ladder = LADDER_LEFT;
	  walls[LEFT_WALL_3D(tx, ty, nz)] = false;
	}
      } else {
	if (dx == -1) {
	  ladder = LADDER_FORWARD;
	  walls[UP_WALL_3D(tx, ty, nz)] = false;
	} else {
	  ladder = LADDER_BACKWARD;
	  walls[DOWN_WALL_3D(tx, ty, nz)] = false;
	}
      }
      if(dz == -1) {
	walls[FLOOR_3D(tx, ty, tz)] = false;
	used[nz * width * height + ty * width + tx] = true;
	if(ladder == LADDER_FORWARD) ladder = LADDER_BACKWARD;
	else if (ladder == LADDER_BACKWARD) ladder = LADDER_FORWARD;
	if(ladder == LADDER_RIGHT) ladder = LADDER_LEFT;
	else if (ladder == LADDER_LEFT) ladder = LADDER_RIGHT;
	ladders[nz * width * height + ty * width + tx] = ladder;
      }
      else {
	walls[ROOF_3D(tx, ty, tz)] = false;
	used[nz * width * height + ty * width + tx] = true;
	ladders[tz * width * height + ty * width + tx] = ladder;
      }

    }

    GenerateDungeon(nx, ny, nz, width, height, floors);
  } while (choices.size() - 1 > 0);
}
