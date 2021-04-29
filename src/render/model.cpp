#include "model.hpp"

Model::Model(const std::string& path) {
	this->loadModel(path);
}

void Model::loadModel(const std::string& path) {

	Assimp::Importer import;

	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	//directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
	for (unsigned int m = 0; m < scene->mNumMeshes; ++m) {
		const aiMesh *mesh = scene->mMeshes[m];
		// iterate over all faces in this mesh
		for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
			auto const &face = mesh->mFaces[j];
			//normally you want just triangles, so iterate over all 3 vertices of the face:
			for (int k = 0; k < face.mNumIndices; ++k) {
				// Now do the magic with 'face.mIndices[k]'
				auto const &vertex = mesh->mVertices[face.mIndices[k]];
				vertices.push_back(vertex.x);
				vertices.push_back(vertex.y);
				vertices.push_back(vertex.z);

				// Same for the normals.
				auto const &normal = mesh->mNormals[face.mIndices[k]];
				vertices.push_back(normal.x);
				vertices.push_back(normal.y);
				vertices.push_back(normal.z);

				// And FINALLY: The UV coordinates!
				if (mesh->HasTextureCoords(0)) {
					// The following line fixed the issue for me now:
					auto const &uv = mesh->mTextureCoords[0][face.mIndices[k]];
					vertices.push_back(uv.x);
					vertices.push_back(uv.y);
				}
				indices.push_back(face.mIndices[k]);
			}
		}
	}
}

BoundaryBox * Model::getBoundaryBox(float scale) {
	glm::vec3 min = glm::vec3(0.0f);
	glm::vec3 max = glm::vec3(0.0f);

	for (int i = 0; i < vertices.size(); i += 8) {
		if (vertices[i] < min.x) {
			min.x = vertices[i];
		}
		if (vertices[i] > max.x) {
			max.x = vertices[i];
		}

		if (vertices[i + 1] < min.y) {
			min.y = vertices[i + 1];
		}
		if (vertices[i + 1] > max.y) {
			max.y = vertices[i + 1];
		}

		if (vertices[i + 2] < min.z) {
			min.z = vertices[i + 2];
		}
		if (vertices[i + 2] > max.z) {
			max.z = vertices[i + 2];
		}
	}

	return new BoundaryBox(min * scale, max * scale);
}
