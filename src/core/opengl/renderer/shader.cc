#include "shader.h"

#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "file_not_found.h"
#include "gl.h"

ShaderProgram::ShaderProgram(const std::string &vertex_shader_path,
                             const std::string &fragment_shader_path,
                             const std::string &geometry_shader_path)
    : program_id_(0),
      vertex_shader_(ReadFromFile(vertex_shader_path).c_str()),
      fragment_shader_(ReadFromFile(fragment_shader_path).c_str()),
      geometry_shader_("") {
  if (vertex_shader_.IsCompiled() && fragment_shader_.IsCompiled()) {
    int is_success;
    char what[512];

    program_id_ = glCreateProgram();
    AttachShaders();
    glLinkProgram(program_id_);
    glGetProgramiv(program_id_, GL_LINK_STATUS, &is_success);
    if (!is_success) {
      glGetProgramInfoLog(program_id_, 512, nullptr, what);
      std::cerr << "[ERROR] Compilation aborted with next message:\n";
      std::cerr << what << std::endl;
      // TODO error handling
      // error text in what var
      throw -1;
    }
    FreeCompiledShaders();
  }
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(program_id_); }

void ShaderProgram::Use() const { glUseProgram(program_id_); }

std::string ShaderProgram::ReadFromFile(const std::string &path) {
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

void ShaderProgram::AttachShaders() {
  glAttachShader(program_id_, vertex_shader_.GetShaderID());
  glAttachShader(program_id_, fragment_shader_.GetShaderID());
}

void ShaderProgram::FreeCompiledShaders() {
  vertex_shader_.FreeShader();
  fragment_shader_.FreeShader();
  geometry_shader_.FreeShader();
}

int ShaderProgram::GetUniformPos(const std::string &name) {
  return glGetUniformLocation(program_id_, name.c_str());
}

void ShaderProgram::UniformMatrix4fv(const std::string &name,
                                     const glm::mat4 &matrix) {
  glUniformMatrix4fv(GetUniformPos(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
