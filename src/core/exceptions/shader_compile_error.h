#ifndef SRC_CORE_EXCEPTIONS_SHADERCOMPILEERROR_H_
#define SRC_CORE_EXCEPTIONS_SHADERCOMPILEERROR_H_

#include <exception>
#include <string>

class ShaderCompileError : std::exception {
 public:
  explicit ShaderCompileError(const std::string &msg) {
    _error_string = "Shader error with: " + msg;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return _error_string.c_str();
  }

 private:
  std::string _error_string;
};

#endif  // SRC_CORE_EXCEPTIONS_SHADERCOMPILEERROR_H_
