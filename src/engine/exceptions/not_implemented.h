#ifndef SRC_ENGINE_EXCEPTIONS_NOT_IMPLEMENTED_H_
#define SRC_ENGINE_EXCEPTIONS_NOT_IMPLEMENTED_H_

#include <exception>

class NotImplemented : std::exception {
  const char *what() const noexcept override {
    return "Not implemented";
  }
};

#endif // SRC_ENGINE_EXCEPTIONS_NOT_IMPLEMENTED_H_
