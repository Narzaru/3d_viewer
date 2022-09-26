#ifndef SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_
#define SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_

#include <glm/vec3.hpp>

struct Transform {
  Transform();
  Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s);
  void set(glm::vec3 p, glm::vec3 r, glm::vec3 s);
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

#endif // SRC_ENGINE_OBJECT_COMPONENTS_TRANSFORM_H_
