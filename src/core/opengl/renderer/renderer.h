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

namespace s21::renderer {
// The renderer class responsible for displaying the model in a world
class Renderer {
 public:
  Renderer() = default;
  void AttachMeshes(std::vector<Mesh> &&meshes);
  void Draw() const;

 private:
  std::vector<Mesh> meshes_;
};
}  // namespace s21::renderer

#endif  // SRC_ENGINE_RENDERER_RENDERER_H_
