#include "renderer.h"

#include "core/opengl/mesh/mesh_loader.h"
#include "texture.h"

namespace s21::renderer {
void Renderer::Draw() const {
  for (const Mesh &item : meshes_) {
    item.Draw();
  }
}
void Renderer::AttachMeshes(std::vector<Mesh> &&meshes) {
  meshes_ = std::move(meshes);
}
}  // namespace s21::renderer