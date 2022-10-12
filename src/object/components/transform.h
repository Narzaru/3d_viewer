#ifndef SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_
#define SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_

#include <glm/vec3.hpp>

namespace components {
struct Transform {
  Transform();
  Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s);
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};
}  // namespace components

#endif  // SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_
