#include "dungeona1generator3d.hpp"
#include <base/location.hpp>
#include <utility>
#include <base/configuration.hpp>

const float wall_height = 6.0f;
const float wall_width = 0.5f;

DungeonA1Generator3D::DungeonA1Generator3D(int floors) : DungeonGenerator(floors) {}


void DungeonA1Generator3D::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  FlatGenerator::Generate(location, width, height, chunk_width, chunk_height, vertices_number);
  GetDefaultTexture() = GetDefaultTexture();
  used.clear();
  for (size_t i = 0; i < width * height * floors; i++)
    used.push_back(false);

  walls.clear();
  for (size_t i = 0; i < width * (height * 2 + 2); i ++) //// ????
    walls.push_back(true);

  ladders.clear();
  for (size_t i = 0; i < width * height * floors; i++)
    ladders.push_back(NO_LADDER);

  GenerateDungeon(0, 0, 0, width, height, floors);

  //  PrintDungeon3D(height, width);
  /*

  for(size_t i = 0; i < width + 1; i ++) {
    for(size_t j = 0; j < height; j ++) {
      if(walls[UP_WALL(i, j)]) { 
	if(i == width)
	  location->GetChunk(width - 1, j)->AddObj(create_wall(glm::vec3(chunk_width * i - 0.5f, wall_height * 0.5f, chunk_height * 0.5f + chunk_height * j), glm::vec3(wall_width, wall_height, chunk_height), GetDefaultTexture()));
	else
	  location->GetChunk(i, j)->AddObj(create_wall(glm::vec3(chunk_width * i, wall_height * 0.5f, chunk_height * 0.5f + chunk_height * j), glm::vec3(wall_width, wall_height, chunk_height), GetDefaultTexture()));
      }
    }
  }

  
  for(size_t i = 0; i < height + 1; i ++) {
    for(size_t j = 0; j < width; j ++) {
      if(walls[RIGHT_WALL(j, i)]) {
	if(i == height)
	  location->GetChunk(j, height - 1)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, wall_height * 0.5f, chunk_height * i - 0.3f), glm::vec3(chunk_width, wall_height, wall_width), GetDefaultTexture()));
	else
	  location->GetChunk(j, i)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, wall_height * 0.5f, chunk_height * i - 0.3f), glm::vec3(chunk_width, wall_height, wall_width), GetDefaultTexture()));
      }
    }
  }

  for (size_t i = 0; i < height; i ++) {
    for (size_t j = 0; j < width; j ++) {
      location->GetChunk(j, i)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, wall_height, chunk_height * i + 0.5f * chunk_height), glm::vec3(chunk_width, wall_width, chunk_height), GetDefaultTexture()));

    }
  }
  */
}

void DungeonA1Generator3D::GenerateDungeon(int tx, int ty, int tz, int width, int height, int floors) {
  used[tz * width * height + ty * width + tx] = true;
  std::vector<std::tuple<int, int, int>> choices;
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
	if (!used[nz * width * height + ny * width + nx])
	  choices.push_back({nx, ny, nz});
	// Go up
	nz = tz + 1;
	if (!used[nz * width * height + ny * width + nx] &&
	    !used[nz * width * height + ty * width + tx])
	  choices.push_back({nx, ny, nz});
	// Go down
	nz = tz - 1;
	if (!used[nz * width * height + ny * width + nx] &&
	    !used[nz * width * height + ty * width + tx])
	  choices.push_back({nx, ny, nz});
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

    GenerateDungeon(nx, ny, nz, width, height, floors);
  } while (choices.size() - 1 > 0);
}

