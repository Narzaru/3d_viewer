#ifndef SRC_ENGINE_SHADER_H_
#define SRC_ENGINE_SHADER_H_

#include <cstdint>
#include <glm/mat4x4.hpp>
#include <string>
#include <vector>

class ShaderProgram {
  using uint = std::uint32_t;

 public:
  ShaderProgram() = delete;
  ShaderProgram(const std::string &vertex_shader_path,
                const std::string &fragment_shader_path);

  ShaderProgram(const std::string &vertex_shader_path,
                const std::string &fragment_shader_path,
                const std::string &geometry_shader_path);

  ~ShaderProgram();

  void Complete();
  void Use();

  void UniformMatrix4fv(const std::string &name, const glm::mat4 &matrix);
  int GetUniformPos(const std::string &name);

 private:
  std::string ReadFromFile(const std::string &path);
  uint CompileShader(const char *code, uint type);
  void AttachShaders();
  void FreeCompiledShaders();

  uint program_id_;
  uint vertex_shader_id_;
  uint fragment_shader_id_;
  uint geometry_shader_id_;
};

#endif  // SRC_ENGINE_SHADER_H_
