#ifndef SRC_CORE_OPENGL_SHADER_SHADER_H_
#define SRC_CORE_OPENGL_SHADER_SHADER_H_

namespace s21::shaders {

enum class ShaderType {
  kVertexShader,
  kFragmentShader,
  kGeometryShader,
  kBaseShader
};

class BaseShader {
 public:
  BaseShader(const BaseShader &other) = delete;
  BaseShader &operator=(const BaseShader &other) = delete;

  explicit BaseShader(ShaderType type = ShaderType::kBaseShader);
  explicit BaseShader(const char *source_code, ShaderType type);
  BaseShader(BaseShader &&other) noexcept;
  BaseShader &operator=(BaseShader &&other) noexcept;

  virtual ~BaseShader();

  [[nodiscard]] int GetShaderID() const;
  BaseShader &CompileFromSource(const char *source_code);
  void FreeShader();
  [[nodiscard]] bool IsCompiled() const;

 private:
  int ProvideGlType();

  bool is_compiled_;
  ShaderType type_;
  int id_;
};

class VertexShader final : public BaseShader {
 public:
  VertexShader() : BaseShader(ShaderType::kVertexShader) {};
  explicit VertexShader(const char *source_code)
      : BaseShader(source_code, ShaderType::kVertexShader) {}
};

class FragmentShader final : public BaseShader {
 public:
  FragmentShader() : BaseShader(ShaderType::kFragmentShader) {}
  explicit FragmentShader(const char *source_code)
      : BaseShader(source_code, ShaderType::kFragmentShader) {}
};

class GeometryShader final : public BaseShader {
 public:
  GeometryShader() : BaseShader(ShaderType::kGeometryShader) {}
  explicit GeometryShader(const char *source_code)
      : BaseShader(source_code, ShaderType::kGeometryShader) {}
};

}  // namespace s21::shaders

#endif  // SRC_CORE_OPENGL_SHADER_SHADER_H_
