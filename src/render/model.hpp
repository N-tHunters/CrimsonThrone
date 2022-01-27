// Copyright 2021 N-tHunters

#pragma once

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include <assimp/Importer.hpp>

#include <physics/boundary.hpp>
#include <render/mesh.hpp>

struct Model {
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
  explicit Model(const std::string& path);
  BoundaryBox* getBoundaryBox(float scale);
  BoundaryBox* getBoundaryBox();
 private:
  void loadModel(const std::string& path);
  void processNode(aiNode *node, const aiScene *scene);
};
