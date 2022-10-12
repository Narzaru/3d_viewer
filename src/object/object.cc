#include "object.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>

namespace s21 {
glm::mat4* Object::view_matrix_{nullptr};
glm::mat4* Object::projection_matrix_{nullptr};

Object::Object()
    : mesh_loader_(),
      transform_(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(1.0)),
      renderer_() {}

components::Transform& Object::Transform() { return transform_; }

void Object::LoadMeshesFromFile(const std::string& path) {
  std::vector<s21::Mesh> meshes = mesh_loader_.LoadFromFile(path);
  renderer_.AttachMeshes(std::move(meshes));
}

void Object::Draw() const { renderer_.Draw(); }

void Object::link_view_matrix(glm::mat4* view_matrix) {
  view_matrix_ = view_matrix;
}

void Object::link_projection_matrix(glm::mat4* projection_matrix) {
  projection_matrix_ = projection_matrix;
}

glm::mat4 Object::GetResultMatrix() {
  glm::mat4 translate = glm::translate(glm::mat4(1.f), transform_.position);
  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(transform_.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  rotation = glm::rotate(rotation, glm::radians(transform_.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  rotation = glm::rotate(rotation, glm::radians(transform_.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform_.scale);
  return translate * scale * rotation;
}
}  // namespace s21