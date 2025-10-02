#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "mesh.hpp"
#include "shader.hpp"

class Model {
public:
  Model(const char *path, const std::string &directory);
  void Draw(Shader &shader);

private:
  const aiScene *scene;
  std::vector<Mesh> meshes;
  std::vector<Texture> textures_loaded;
  std::string directory;

  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};
