#include "shader_program.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "gl.h"

namespace s21::shaders {
ShaderProgram::ShaderProgram()
    : id_(0),
      is_have_vertex_shader_(false),
      is_have_fragment_shader_(false),
      is_have_geometry_shader_(false),
      vertex_shader_(),
      fragment_shader_(),
      geometry_shader_() {}

ShaderProgram::ShaderProgram(s21::shaders::ShaderProgram &&other) noexcept
    : id_(other.id_),
      is_have_vertex_shader_(other.is_have_vertex_shader_),
      is_have_fragment_shader_(other.is_have_fragment_shader_),
      is_have_geometry_shader_(other.is_have_geometry_shader_),
      vertex_shader_(std::move(other.vertex_shader_)),
      fragment_shader_(std::move(other.fragment_shader_)),
      geometry_shader_(std::move(other.geometry_shader_)) {
  other.id_ = 0;
  other.is_have_vertex_shader_ = false;
  other.is_have_fragment_shader_ = false;
  other.is_have_geometry_shader_ = false;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other) noexcept {
  if (this != &other) {
    FreeShaders();
    FreeProgram();

    id_ = other.id_;
    is_have_vertex_shader_ = other.is_have_vertex_shader_;
    is_have_fragment_shader_ = other.is_have_fragment_shader_;
    is_have_geometry_shader_ = other.is_have_geometry_shader_;
    vertex_shader_ = std::move(other.vertex_shader_);
    fragment_shader_ = std::move(other.fragment_shader_);
    geometry_shader_ = std::move(other.geometry_shader_);

    other.id_ = 0;
    other.is_have_vertex_shader_ = false;
    other.is_have_fragment_shader_ = false;
    other.is_have_geometry_shader_ = false;
  }
  return *this;
}

ShaderProgram::~ShaderProgram() {
  FreeShaders();
  FreeProgram();
}

void ShaderProgram::SetVertexShader(VertexShader &&shader) {
  is_have_vertex_shader_ = true;
  vertex_shader_ = std::move(shader);
}

void ShaderProgram::SetFragmentShader(FragmentShader &&shader) {
  is_have_fragment_shader_ = true;
  fragment_shader_ = std::move(shader);
}

void ShaderProgram::SetGeometryShader(GeometryShader &&shader) {
  is_have_geometry_shader_ = true;
  geometry_shader_ = std::move(shader);
}

void ShaderProgram::Compile() {
  id_ = glCreateProgram();
  if (!AttachShaders()) {
    std::cerr << "[ERROR] not enough base shaders" << std::endl;
    FreeShaders();
    FreeProgram();
    return;
  }

  glLinkProgram(id_);

  int is_success;
  char what[512];
  glGetProgramiv(id_, GL_LINK_STATUS, &is_success);
  if (!is_success) {
    glGetProgramInfoLog(id_, 512, nullptr, what);
    std::cerr << "[ERROR] Program compilation aborted with next message:\n";
    std::cerr << what << std::endl;
    FreeShaders();
    FreeProgram();
    return;
  }

  FreeShaders();
}

bool ShaderProgram::IsCompiled() const { return id_ != 0; }

bool ShaderProgram::AttachShaders() {
  if (is_have_vertex_shader_ && is_have_fragment_shader_) {
    glAttachShader(id_, vertex_shader_.GetShaderID());
    glAttachShader(id_, fragment_shader_.GetShaderID());
    if (is_have_geometry_shader_) {
      glAttachShader(id_, geometry_shader_.GetShaderID());
    }
    return true;
  } else {
    return false;
  }
}

void ShaderProgram::FreeShaders() {
  vertex_shader_.FreeShader();
  fragment_shader_.FreeShader();
  geometry_shader_.FreeShader();
}

void ShaderProgram::FreeProgram() {
  if (id_ != 0) {
    glDeleteProgram(id_);
    id_ = 0;
  }
}
void ShaderProgram::Use() const { glUseProgram(id_); }

int ShaderProgram::GetUniformPos(const std::string &name) const {
  return glGetUniformLocation(id_, name.c_str());
}

void ShaderProgram::UniformMatrix4fv(const std::string &name,
                                     const glm::mat4 &matrix) const {
  glUniformMatrix4fv(GetUniformPos(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

}  // namespace s21::shaders
