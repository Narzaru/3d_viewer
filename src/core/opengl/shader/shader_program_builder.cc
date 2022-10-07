#include "shader_program_builder.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "core/exceptions/file_not_found.h"

namespace s21::shaders {

ShaderProgramBuilder& ShaderProgramBuilder::AddVertexShaderFromFile(
    const std::string& path) {
  VertexShader shader(ReadFromFile(path).c_str());
  shader_program_.SetVertexShader(std::move(shader));
  return *this;
}

ShaderProgramBuilder& ShaderProgramBuilder::AddFragmentShaderFromFile(
    const std::string& path) {
  FragmentShader shader(ReadFromFile(path).c_str());
  shader_program_.SetFragmentShader(std::move(shader));
  return *this;
}

ShaderProgramBuilder& ShaderProgramBuilder::AddGeometryShaderFromFile(
    const std::string& path) {
  GeometryShader shader(ReadFromFile(path).c_str());
  shader_program_.SetGeometryShader(std::move(shader));
  return *this;
}

ShaderProgram&& ShaderProgramBuilder::Build() {
  shader_program_.Compile();
  return std::move(shader_program_);
}

std::string ShaderProgramBuilder::ReadFromFile(const std::string& path) {
  std::ifstream file_stream;
  file_stream.open(path);

  if (file_stream.is_open()) {
    std::stringstream buffer;
    std::string file_content;
    buffer << file_stream.rdbuf();
    file_content = buffer.str();
    file_stream.close();
    return file_content;
  } else {
    throw FileNotFound(path);
  }
}

}  // namespace s21::shaders