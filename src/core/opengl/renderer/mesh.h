#ifndef SRC_ENGINE_RENDERER_MESH_H_
#define SRC_ENGINE_RENDERER_MESH_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "texture.h"
#include "vertex.h"

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
  vector<Vertex> vertices;
  vector<uint> indices;
  static map<std::string, Texture> texture_pool_;
  uint VAO;  // Vertex Arrays Objects
  uint VBO;  // Vertex Buffer Objects
  uint EBO;  // Element Buffer Objects (vertex indices)
};

#endif  // SRC_ENGINE_RENDERER_MESH_H_