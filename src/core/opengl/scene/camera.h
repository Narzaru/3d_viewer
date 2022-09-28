// ! Class is not implemented

#ifndef SRC_ENGINE_SCENE_CAMERA_H_
#define SRC_ENGINE_SCENE_CAMERA_H_

#include <glm/vec3.hpp>

class Camera {
 public:
  Camera() = delete;
  Camera(const Camera &) = delete;
  Camera(Camera &&) = delete;
  glm::vec3 position;
};

#endif  // SRC_ENGINE_SCENE_CAMERA_H_
