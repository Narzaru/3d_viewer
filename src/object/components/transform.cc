#include "transform.h"
#include <utility>

Transform::Transform()
    : position(glm::vec3(0.0f)),
      rotation(glm::vec3(0.0f)),
      scale(glm::vec3(0.0f)) {}

Transform::Transform(glm::vec3 p, glm::vec3 r, glm::vec3 s)
    : position(p),
      rotation(r),
      scale(s) {}

void Transform::set(glm::vec3 p, glm::vec3 r, glm::vec3 s) {
  position = glm::vec3(p);
  rotation = glm::vec3(r);
  scale = glm::vec3(s);
}
