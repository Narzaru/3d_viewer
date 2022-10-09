#ifndef SRC_ENGINE_RENDERER_RENDERER_H_
#define SRC_ENGINE_RENDERER_RENDERER_H_

#include <assimp/scene.h>

#include <map>
#include <string>

#include "core/opengl/mesh/mesh.h"
#include "core/opengl/mesh/mesh_loader.h"
#include "core/opengl/shader/shader_program.h"
#include "core/opengl/shader/shader_program_builder.h"
#include "texture.h"

// The renderer class responsible for displaying the model in a world
class Renderer {
 public:
  enum class VertexConnectionType { kTriangles, kLines, kNone };

  Renderer() = default;
  explicit Renderer(const std::string &file_path);
  void LoadMeshesFromFile(const std::string &file_path);
  void AttachShaderProgram(s21::shaders::ShaderProgram &&shader_program);
  void Draw(VertexConnectionType type = VertexConnectionType::kTriangles);

 private:
  MeshLoader mesh_loader_;
  std::vector<Mesh> meshes_;
  s21::shaders::ShaderProgram shader_program_;
};

#endif  // SRC_ENGINE_RENDERER_RENDERER_H_
