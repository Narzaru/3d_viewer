#ifndef SRC_CORE_EXCEPTIONS_FILE_NOT_FOUND_H_
#define SRC_CORE_EXCEPTIONS_FILE_NOT_FOUND_H_

#include <exception>
#include <string>

class FileNotFound : std::exception {
 public:
  explicit FileNotFound(const std::string &file_path) {
    _error_string = "Cant open file " + file_path;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return _error_string.c_str();
  }

 private:
  std::string _error_string;
};

#endif  // SRC_CORE_EXCEPTIONS_FILE_NOT_FOUND_H_
