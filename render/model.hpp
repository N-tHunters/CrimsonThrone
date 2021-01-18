#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.hpp"

class Model 
{
    public:
    	std::vector<GLfloat> vertices;
    	std::vector<GLuint> indices;
        explicit Model(char* path);
    private:
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
};