#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.hpp"
#include <physics/boundary.hpp>

class Model
{
public:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	explicit Model(const std::string& path);

	BoundaryBox* getBoundaryBox(float scale);
private:
	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
};

#endif