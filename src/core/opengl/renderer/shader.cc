#include "shader.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

#include "gl.h"

ShaderProgram::ShaderProgram(const std::string &vertex_shader_path,
                             const std::string &fragment_shader_path)
    : program_id_(0),
      vertex_shader_id_(0),
      fragment_shader_id_(0),
      geometry_shader_id_(0) {
  std::string vertex_code = ReadFromFile(vertex_shader_path);
  std::string fragment_code = ReadFromFile(fragment_shader_path);

  vertex_shader_id_ = CompileShader(vertex_code.c_str(), GL_VERTEX_SHADER);
  fragment_shader_id_ =
      CompileShader(fragment_code.c_str(), GL_FRAGMENT_SHADER);
}

ShaderProgram::ShaderProgram(const std::string &vertex_shader_path,
                             const std::string &fragment_shader_path,
                             const std::string &geometry_shader_path)
    : ShaderProgram(vertex_shader_path, fragment_shader_path) {
  std::string geometry_code = ReadFromFile(geometry_shader_path);
  geometry_shader_id_ =
      CompileShader(geometry_code.c_str(), GL_GEOMETRY_SHADER);
}

ShaderProgram::~ShaderProgram() { glDeleteProgram(program_id_); }

void ShaderProgram::Complete() {
  int is_success;
  char what[512];

  program_id_ = glCreateProgram();
  AttachShaders();
  glLinkProgram(program_id_);
  glGetProgramiv(program_id_, GL_LINK_STATUS, &is_success);
  if (!is_success) {
    glGetProgramInfoLog(program_id_, 512, nullptr, what);
    // TODO error handling
    // error text in what var
    throw -1;
  }
  FreeCompiledShaders();
}

void ShaderProgram::Use() { glUseProgram(program_id_); }

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
    // TODO error handling
    // cant open file
    throw -1;
  }
}

uint ShaderProgram::CompileShader(const char *code, uint type) {
  uint shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &code, nullptr);
  glCompileShader(shader_id);

  int is_success;
  char what[512];
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_success);
  if (!is_success) {
    glGetShaderInfoLog(shader_id, 512, nullptr, what);
    // TODO error handling
    // error text in what var
    throw -1;
  } else {
    return shader_id;
  }
}

void ShaderProgram::AttachShaders() {
  if (vertex_shader_id_ != 0) {
    glAttachShader(program_id_, vertex_shader_id_);
  }
  if (fragment_shader_id_ != 0) {
    glAttachShader(program_id_, fragment_shader_id_);
  }
  if (geometry_shader_id_ != 0) {
    glAttachShader(program_id_, geometry_shader_id_);
  }
}

void ShaderProgram::FreeCompiledShaders() {
  if (vertex_shader_id_ != 0) {
    glDeleteShader(vertex_shader_id_);
    vertex_shader_id_ = 0;
  }
  if (fragment_shader_id_ != 0) {
    glDeleteShader(fragment_shader_id_);
    fragment_shader_id_ = 0;
  }
  if (geometry_shader_id_ != 0) {
    glDeleteShader(geometry_shader_id_);
    geometry_shader_id_ = 0;
  }
}

int ShaderProgram::GetUniformPos(const std::string &name) {
  return glGetUniformLocation(program_id_, name.c_str());
}

void ShaderProgram::UniformMatrix4fv(const std::string &name,
                                     const glm::mat4 &matrix) {
  glUniformMatrix4fv(GetUniformPos(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
