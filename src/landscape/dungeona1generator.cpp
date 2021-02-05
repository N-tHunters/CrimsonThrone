#include "dungeona1generator.hpp"
#include <base/location.hpp>
#include <utility>

const float wall_height = 10.0f;

DungeonA1Generator::DungeonA1Generator(int floors) : floors(floors) {}

void DungeonA1Generator::Generate(Location * location, size_t width, size_t height, int chunk_width, int chunk_height, int vertices_number) {
  FlatGenerator::Generate(location, width, height, chunk_width, chunk_height, vertices_number);
  used.clear();
  for(size_t i = 0; i < width * height; i++)
    used.push_back(false);

  walls.clear();
  for(size_t i = 0; i < width * (height * 2 + 2); i ++)
    walls.push_back(true);

  GenerateDungeon(0, 0, width, height);

  PrintDungeon(height, width);

  for(size_t i = 0; i < width + 1; i ++) {
    for(size_t j = 0; j < height; j ++) {
      if(walls[i * (height * 2 + 1) + j]) {
	if(i == width)
	  location->GetChunk(width - 1, j)->AddObj(create_wall(glm::vec3(chunk_width * i - 0.5f, 0.0f, chunk_height * 0.5f + chunk_height * j), glm::vec3(2.0f, wall_height, chunk_height), "resources/textures/stone.jpg"));
	else
	  location->GetChunk(i, j)->AddObj(create_wall(glm::vec3(chunk_width * i, 0.0f, chunk_height * 0.5f + chunk_height * j), glm::vec3(2.0f, wall_height, chunk_height), "resources/textures/stone.jpg"));
      }
    }
  }

  
  for(size_t i = 0; i < height + 1; i ++) {
    for(size_t j = 0; j < width; j ++) {
      if(walls[height + (height * 2 + 1) * j + i]) {
	if(i == height)
	  location->GetChunk(j, height - 1)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, 0.0f, chunk_height * i - 0.3f), glm::vec3(chunk_width, wall_height, 2.0f), "resources/textures/stone.jpg"));
	else
	  location->GetChunk(j, i)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, 0.1f, chunk_height * i - 0.3f), glm::vec3(chunk_width, wall_height, 2.0f), "resources/textures/stone.jpg"));
      }
    }
  }
  
  for(size_t i = 0; i < height; i ++) {
    for(size_t j = 0; j < width; j ++) {
	  location->GetChunk(j, i)->AddObj(create_wall(glm::vec3(chunk_width * 0.5f + chunk_width * j, wall_height, chunk_height * i + 0.5f * chunk_height), glm::vec3(chunk_width, 2.0f, chunk_height), "resources/textures/stone.jpg"));

    }
  }
}

void DungeonA1Generator::GenerateDungeon(int tx, int ty, int mx, int my) {
  used[tx * mx + ty] = true;
  std::vector<std::pair<int,int>> choices;
  do {
    choices.clear();
    for(int i = -1; i < 2; i++) {
      for(int j = -1; j < 2; j++) {
	if(abs(i + j) != 1) continue;
	int nx = tx + i;
	int ny = ty + j;
	if(nx < 0 || ny < 0 || nx >= mx || ny >= my) continue;
	if(used[nx * mx + ny]) continue;
	choices.push_back({nx, ny});
      }
    }
    if (choices.size() == 0) break;

    int choice = rand() % choices.size();
    int nx = choices[choice].first;
    int ny = choices[choice].second;

    int dx = nx - tx;
    int dy = ny - ty;

    if(dx != 0) {
      if(dx == -1) {
	walls[my + (my * 2 + 1) * ty + tx] = false;
      } else {
       	walls[my + (my * 2 + 1) * ty + nx] = false;
      }
    } else {
      if(dy == -1) {
	walls[(my * 2 + 1) * ty + tx] = false;
      } else {
       	walls[(my * 2 + 1) * ny + tx] = false;
      }
    }
    
    GenerateDungeon(nx, ny, mx, my);
  } while (choices.size() - 1 > 0);
}


void DungeonA1Generator::PrintDungeon(int height, int width) {
  int q = 0;
  for(size_t i = 0; i < height * 2 + 1; i++) {
    if(i % 2 == 0) {
      printf("#");
      for(size_t j = 0; j < width; j++) {
	if(walls[q++])
	  printf("##");
	else
	  printf(" #");
      }
    } else {
      for(size_t j = 0; j < width + 1; j++) {
	if(walls[q++])
	  printf("# ");
	else
	  printf("  ");
      }
    }
    puts("");
  }
}
