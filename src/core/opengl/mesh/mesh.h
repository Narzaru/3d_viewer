#ifndef CORE_OPENGL_MESH_MESH__H_
#define CORE_OPENGL_MESH_MESH__H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "core/opengl/renderer/texture.h"
#include "core/opengl/renderer/vertex.h"

namespace s21 {
class Mesh {
 public:
  Mesh(std::vector<Vertex> vertices, std::vector<uint> indices);
  ~Mesh();
  Mesh(const Mesh &other) = delete;
  Mesh(Mesh &&other) noexcept;

  void Draw() const;
  void SetupMesh();

 private:
  // Properties
  uint number_of_vertices{0};
  uint number_of_faces{0};
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  static std::map<std::string, Texture> texture_pool_;
  uint VAO;  // Vertex Arrays Objects
  uint VBO;  // Vertex Buffer Objects
  uint EBO;  // Element Buffer Objects (Indices Buffer Object)
};
}  // namespace s21
#endif
