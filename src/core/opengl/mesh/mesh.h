#ifndef CORE_OPENGL_MESH_MESH__H_
#define CORE_OPENGL_MESH_MESH__H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "core/opengl/renderer/texture.h"
#include "core/opengl/renderer/vertex.h"

class Mesh {
 public:
  template <typename T>
  using vector = std::vector<T>;

  template <typename Key, typename Val>
  using map = std::map<Key, Val>;

  using string = std::string;
  using uint = std::uint32_t;

  Mesh(vector<Vertex> vertices, vector<uint> indices,
       const map<string, Texture> &textures);
  Mesh(vector<Vertex> vertices, vector<uint> indices);
  ~Mesh();
  Mesh(const Mesh &other) = delete;
  Mesh(Mesh &&other) noexcept;

  void DrawTriangles() const;
  void DrawLines() const;
  void DrawPoints() const;
  void SetupMesh();

 private:
  // Properties
  uint number_of_vertices{0};
  uint number_of_faces{0};
  vector<Vertex> vertices;
  vector<uint> indices;
  static map<std::string, Texture> texture_pool_;
  uint VAO;  // Vertex Arrays Objects
  uint VBO;  // Vertex Buffer Objects
  uint EBO;  // Element Buffer Objects (Indices Buffer Object)
};

#endif
