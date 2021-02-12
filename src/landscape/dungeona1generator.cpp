#include "dungeona1generator.hpp"
#include <base/location.hpp>
#include <utility>
#include <base/configuration.hpp>

const float wall_height = 6.0f;
const float wall_width = 0.5f;

DungeonA1Generator::DungeonA1Generator() : DungeonGenerator(1) {}

void DungeonA1Generator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  FlatGenerator::Generate(location, width, height, chunk_width, chunk_height, vertices_number);
  GetDefaultTexture() = GetDefaultTexture();
  used.clear();
  for (size_t i = 0; i < width * height; i++)
    used.push_back(false);

  walls.clear();
  for (size_t i = 0; i < width * (height * 2 + 1) + height; i ++)
    walls.push_back(true);

  GenerateDungeon(0, 0, width, height);

  PrintDungeon(height, width);


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
}

void DungeonA1Generator::GenerateDungeon(int tx, int ty, int width, int height) {
  used[ty * width + tx] = true;
  std::vector<std::pair<int, int>> choices;
  do {
    choices.clear();
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if (abs(i + j) != 1) continue;
        int nx = tx + i;
        int ny = ty + j;
        if (nx < 0 || ny < 0 || nx >= width || ny >= height) continue;
        if (used[ny * width + nx]) continue;
        choices.push_back({nx, ny});
      }
    }
    if (choices.size() == 0) break;

    int choice = rand() % choices.size();
    int nx = choices[choice].first;
    int ny = choices[choice].second;

    int dy = ny - ty;
    int dx = nx - tx;

    if (dy != 0) {
      if (dy == -1) {
        walls[RIGHT_WALL(tx, ty)] = false;
      } else {
        walls[LEFT_WALL(tx, ty)] = false;
      }
    } else {
      if (dx == -1) {
        walls[UP_WALL(tx, ty)] = false;
      } else {
        walls[DOWN_WALL(tx, ty)] = false;
      }
    }

    GenerateDungeon(nx, ny, width, height);
  } while (choices.size() - 1 > 0);
}

