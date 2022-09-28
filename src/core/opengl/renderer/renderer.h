#ifndef SRC_ENGINE_RENDERER_RENDERER_H_
#define SRC_ENGINE_RENDERER_RENDERER_H_

#include <assimp/scene.h>

#include <map>
#include <string>

#include "mesh.h"
#include "texture.h"

class Renderer {
 public:
  enum class VertexConnectionType { kTriangles, kLines };
  Renderer() = default;
  explicit Renderer(const std::string &file_path);
  // Load vertices from a file
  void LoadFromFile(const std::string &file_path);
  void Axes();
  // If you have a gl context, draw meshes
  void DrawMeshes(VertexConnectionType type);

 private:
  void ProcessNode(const aiNode *node, const aiScene *scene);
  Mesh LoadMesh(const aiMesh *mesh);
  std::vector<Mesh> meshes_;
};

#endif  // SRC_ENGINE_RENDERER_RENDERER_H_
