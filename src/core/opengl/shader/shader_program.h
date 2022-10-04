#ifndef CORE_OPENGL_SHADER_SHADER_PROGRAM_H_
#define CORE_OPENGL_SHADER_SHADER_PROGRAM_H_

#include <array>
#include <glm/mat4x4.hpp>
#include <string>

#include "shader.h"

namespace s21::shaders {
class ShaderProgram {
 public:
  ShaderProgram();
  ShaderProgram(s21::shaders::ShaderProgram &&other) noexcept;
  ShaderProgram &operator=(ShaderProgram &&other) noexcept;
  ~ShaderProgram();

  void AddVertexShader(VertexShader &&shader);
  void AddFragmentShader(FragmentShader &&shader);
  void AddGeometryShader(GeometryShader &&shader);
  void Compile();
  [[nodiscard]] bool IsCompiled() const;
  void Use();

  [[nodiscard]] int GetUniformPos(const std::string &name) const;

  void UniformMatrix4fv(const std::string &name, const glm::mat4 &matrix);

 private:
  bool AttachShaders();
  void FreeShaders();
  void FreeProgram();

  int id_;
  bool is_have_vertex_shader_;
  bool is_have_fragment_shader_;
  bool is_have_geometry_shader_;
  VertexShader vertex_shader_;
  FragmentShader fragment_shader_;
  GeometryShader geometry_shader_;
};
}  // namespace s21::shaders

#endif  // CORE_OPENGL_SHADER_SHADER_PROGRAM_H_