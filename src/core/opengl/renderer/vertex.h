#ifndef SRC_ENGINE_RENDERER_VERTEX_H_
#define SRC_ENGINE_RENDERER_VERTEX_H_

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex {
  Vertex()
      : v(0.0f),
        vn(0.0f),
        vt(0.0f),
        color(0.0f),
        tangent(0.0f),
        bitangent(0.0f){};

  glm::vec3 v;          // Geometric vertex
  glm::vec3 vn;         // Normal vertex
  glm::vec2 vt;         // Texture coordinates
  glm::vec4 color;      // Vertex color
  glm::vec3 tangent;    // tangent to normal vertex
  glm::vec3 bitangent;  // tangent to tangent and normal vertex
};

#endif  // SRC_ENGINE_RENDERER_VERTEX_H_
