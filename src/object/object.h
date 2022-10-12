#ifndef SRC_ENGINE_OBJECT_OBJECT_H_
#define SRC_ENGINE_OBJECT_OBJECT_H_

#include <glm/vec3.hpp>
#include <string>

#include "core/opengl/renderer/renderer.h"
#include "object/components/transform.h"

namespace s21 {
class Object {
 public:
  Object();
  void LoadMeshesFromFile(const std::string &path);
  [[nodiscard]] components::Transform &Transform();
  void Draw() const;
  static void link_view_matrix(glm::mat4 *view_matrix);
  static void link_projection_matrix(glm::mat4 *projection_matrix);
  glm::mat4 GetResultMatrix();

 private:
  s21::MeshLoader mesh_loader_;
  components::Transform transform_;
  s21::renderer::Renderer renderer_;

  static glm::mat4 *view_matrix_;
  static glm::mat4 *projection_matrix_;
};
}  // namespace s21

#endif  // SRC_ENGINE_OBJECT_OBJECT_H_
