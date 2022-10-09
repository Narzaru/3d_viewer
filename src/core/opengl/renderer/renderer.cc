#include "renderer.h"

#include "core/opengl/mesh/mesh_loader.h"
#include "texture.h"

Renderer::Renderer(const std::string &file_path) {
  LoadMeshesFromFile(file_path);
}

void Renderer::LoadMeshesFromFile(const std::string &file_path) {
  meshes_ = mesh_loader_.LoadFromFile(file_path);
}

void Renderer::Draw(VertexConnectionType type) {
  for (const Mesh &item : meshes_) {
    if (type == VertexConnectionType::kTriangles)
      item.DrawTriangles();
    else if (type == VertexConnectionType::kLines)
      item.DrawLines();
    else
      item.DrawPoints();
  }
}

void Renderer::AttachShaderProgram(
    s21::shaders::ShaderProgram &&shader_program) {
  shader_program_ = std::move(shader_program);
}
