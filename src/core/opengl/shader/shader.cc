#include "shader.h"

#include <iostream>

#include "gl.h"

namespace s21::shaders {

BaseShader::BaseShader(ShaderType type)
    : is_compiled_(false), type_(type), id_(0) {}

BaseShader::BaseShader(const char *source_code, ShaderType type)
    : BaseShader(type) {
  CompileFromSource(source_code);
}

BaseShader::BaseShader(BaseShader &&other) noexcept {
  is_compiled_ = other.is_compiled_;
  type_ = other.type_;
  id_ = other.id_;

  other.is_compiled_ = false;
  other.type_ = ShaderType::kBaseShader;
  other.id_ = 0;
}

BaseShader &BaseShader::operator=(BaseShader &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  FreeShader();

  is_compiled_ = other.is_compiled_;
  type_ = other.type_;
  id_ = other.id_;

  other.is_compiled_ = false;
  other.type_ = ShaderType::kBaseShader;
  other.id_ = 0;

  return *this;
}

BaseShader::~BaseShader() { FreeShader(); }

int BaseShader::GetShaderID() const { return id_; }

BaseShader &BaseShader::CompileFromSource(const char *source_code) {
  id_ = glCreateShader(ProvideGlType());
  glShaderSource(id_, 1, &source_code, nullptr);
  glCompileShader(id_);

  int success = 0;
  char compile_log[512];
  glGetShaderiv(id_, GL_COMPILE_STATUS, &success);

  if (success) {
    is_compiled_ = true;
  } else {
    glGetShaderInfoLog(id_, sizeof(compile_log), nullptr, compile_log);
    std::cerr << "[ERROR] shader compilation aborted with an error: ";
    std::cerr << std::endl << compile_log << std::endl;
  }
  return *this;
}

void BaseShader::FreeShader() {
  if (id_ != 0) {
    is_compiled_ = false;
    type_ = ShaderType::kBaseShader;
    glDeleteShader(id_);
    id_ = 0;
  }
}

bool BaseShader::IsCompiled() const { return is_compiled_; }

int BaseShader::ProvideGlType() {
  switch (type_) {
    case ShaderType::kVertexShader:
      return GL_VERTEX_SHADER;
    case ShaderType::kFragmentShader:
      return GL_FRAGMENT_SHADER;
    case ShaderType::kGeometryShader:
      return GL_GEOMETRY_SHADER;
    default:
      return 0;
  }
}

}  // namespace s21::shaders