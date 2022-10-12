#ifndef CORE_OPENGL_MESH_MESH_LOADER_H_
#define CORE_OPENGL_MESH_MESH_LOADER_H_

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>

#include "core/opengl/mesh/mesh.h"

namespace s21 {
class MeshLoader {
 public:
  MeshLoader() = default;
  std::vector<Mesh> LoadFromFile(const std::string &file_path);

 private:
  void ProcessNode(const aiNode *node, const aiScene *scene);
  static Mesh LoadMesh(const aiMesh *mesh);
  std::vector<Mesh> meshes_;
};
}  // namespace s21
#endif  // CORE_OPENGL_MESH_MESH_LOADER_H_
