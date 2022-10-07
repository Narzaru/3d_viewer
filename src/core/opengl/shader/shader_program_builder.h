#ifndef CORE_OPENGL_SHADER_SHADER_PROGRAM_BUILDER_H_
#define CORE_OPENGL_SHADER_SHADER_PROGRAM_BUILDER_H_

#include <memory>

#include "./shader_program.h"

namespace s21::shaders {

class ShaderProgramBuilder {
 public:
  ShaderProgramBuilder() = default;
  ShaderProgramBuilder &AddVertexShaderFromFile(const std::string &path);
  ShaderProgramBuilder &AddFragmentShaderFromFile(const std::string &path);
  ShaderProgramBuilder &AddGeometryShaderFromFile(const std::string &path);
  [[nodiscard]] s21::shaders::ShaderProgram &&Build();

 private:
  static std::string ReadFromFile(const std::string &path);
  s21::shaders::ShaderProgram shader_program_;
};

}  // namespace s21::shaders

#endif  // CORE_OPENGL_SHADER_SHADER_PROGRAM_BUILDER_H_
