#pragma once

#include "abstractchunk.hpp"
#include <render/models.hpp>
#include <render/textures.hpp>
#include <render/texture.hpp>

class ChunkLoader {
protected:
	float size;
	int vertices_number;
	glm::vec3 position;
public:
	ChunkLoader() {}
	virtual void Load(AbstractChunk *); // Need to be called as a thread
	void LoadEnd(std::vector<std::vector<float>> * height_map,
	             AbstractChunk * chunk,
	             GLuint texture1,
	             GLuint texture2,
	             std::vector<unsigned char> blend_pixels); // This is called in the end
	virtual void LoadObjects(AbstractChunk *);
	virtual bool AreObjectsLoaded();
};
