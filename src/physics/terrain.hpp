/**
 * \file
 * \brief This file contains the declaration of Terrain
 */

#ifndef TERRAIN_H
#define TERRAIN_H

#include <random>
#include <math.h>
#include <array>
#include <base/configuration.hpp>

#include "physicalObj.hpp"

#include <render/shaderLoader.hpp>
#include <render/camera.hpp>
#include <render/shaderHolder.hpp>
#include <render/textures.hpp>

#include <math/vectors.hpp>

/**
 * @brief The physical ground that everyone collides with
 * @details Consists of small triangle tiles that are used to get it's height in certain position
 * @author Altrul
 * @
 */
class Terrain {
protected:
	float size; /**< The width of the whole Terrain in meters */
	float tile_width; /**< The width of one tile in meters */
	
	int vertices_number; /**< The number of vertices in one line */
	
	std::vector<GLfloat> vertices; /**< Vertices in Terrain's Mesh */
	std::vector<unsigned int> indices; /**< Indices in Terrain's Mesh */
	std::vector<std::vector<float>> height; /**< The height map */

	PhysicalObj* obj; /**< The object that contains Mesh and collides */
	
	glm::vec3 position; /**< Global position in one Location */

public:
	Terrain(float,
			int,
			glm::vec3,
			std::vector<std::vector<float>> *,
			GLuint texture1,
			GLuint texture2,
			float texture_scale,
			GLuint blend_texture);

	glm::vec3 getPosition();
	glm::vec3 getOutVector(glm::vec3);
	
	PhysicalObj* getPhysicalObj();

	int getVerticesNumber();

	float getHeight(glm::vec3);
	float getSize();
	float getHeightMap(int x, int y);
	float getTileWidth();

	void draw(ShaderHolder*, Camera*, GLuint, GLuint);
};

#endif
