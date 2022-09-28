#ifndef SRC_ENGINE_OBJECT_OBJECT_H_
#define SRC_ENGINE_OBJECT_OBJECT_H_

#include <glm/vec3.hpp>
#include <string>

#include "core/opengl/renderer/renderer.h"
#include "object/components/transform.h"

namespace s21 {
class Object {
 public:
  Object() = default;
  Object(glm::vec3 instance_position, glm::vec3 instance_rotation,
         glm::vec3 instance_scale, const std::string &model_path)
      : transform_(instance_position, instance_rotation, instance_scale),
        renderer_(model_path) {}

  [[nodiscard]] const Transform &GetTransform() const { return transform_; }

  void SetTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    transform_.set(position, rotation, scale);
  }

  void Draw() {
    renderer_.DrawMeshes(Renderer::VertexConnectionType::kTriangles);
  }

 private:
  Transform transform_;
  Renderer renderer_;
};
}  // namespace s21

#endif  // SRC_ENGINE_OBJECT_OBJECT_H_
