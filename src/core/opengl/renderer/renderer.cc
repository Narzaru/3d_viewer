#include "renderer.h"

#include <assimp/postprocess.h>

#include <assimp/Importer.hpp>
#include <cstdint>
#include <ctime>
#include <glm/vec4.hpp>

#include "texture.h"
#include "vertex.h"

Renderer::Renderer(const std::string &file_path) { LoadFromFile(file_path); }

void Renderer::LoadFromFile(const std::string &file_path) {
  Assimp::Importer importer;
  std::uint32_t mask_of_options = 0;

  mask_of_options |= aiProcess_Triangulate;
  mask_of_options |= aiProcess_GenNormals;
  mask_of_options |= aiProcess_JoinIdenticalVertices;
  mask_of_options |= aiProcess_OptimizeMeshes;
  mask_of_options |= aiProcess_OptimizeGraph;
  mask_of_options |= aiProcess_SortByPType;
  mask_of_options |= aiProcess_CalcTangentSpace;
  const aiScene *scene = importer.ReadFile(file_path, mask_of_options);

  if (scene != nullptr) {
    ProcessNode(scene->mRootNode, scene);
  } else {
    // !TODO add throw error or return
  }
}

void Renderer::Axes() {
  std::array<glm::vec3, 6> vs = {glm::vec3(0.0), glm::vec3(1.0, 0.0, 0.0),
                                 glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0),
                                 glm::vec3(0.0), glm::vec3(0.0, 0.0, 1.0)};
  std::array<glm::vec4, 6> colors = {
      glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec4(1.0, 0.0, 0.0, 1.0),
      glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec4(0.0, 1.0, 0.0, 1.0),
      glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec4(0.0, 0.0, 1.0, 1.0)};
  std::vector<std::uint32_t> indices = {0, 1, 2, 3, 4, 5};
  Vertex vertex;
  std::vector<Vertex> vertices;
  for (int i = 0; i < 6; ++i) {
    vertex.v = vs[i];
    vertex.color = colors[i];
    vertices.push_back(vertex);
  }
  meshes_.emplace_back(std::move(vertices), std::move(indices));
}

void Renderer::DrawMeshes(VertexConnectionType type) {
  for (const Mesh &item : meshes_) {
    if (type == VertexConnectionType::kTriangles)
      item.DrawTriangles();
    else if (type == VertexConnectionType::kLines)
      item.DrawLines();
    else
      item.DrawPoints();
  }
}

void Renderer::ProcessNode(const aiNode *node, const aiScene *scene) {
  for (uint32_t i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }

  for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
    meshes_.push_back(LoadMesh(scene->mMeshes[node->mMeshes[i]]));
  }
}

Mesh Renderer::LoadMesh(const aiMesh *mesh) {
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

#ifdef RANDOM_COLORS
  std::srand(std::time(nullptr));
#endif  // RANDOM_COLORS

  // Process vertices
  for (std::uint32_t i = 0; i < mesh->mNumVertices; ++i) {
    Vertex vertex;
    glm::vec4 vector;

    // Geometric vertex
    if (mesh->mVertices != nullptr) {
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
    } else {
      vector = glm::vec4(0.0f);
    }
    vertex.v = vector;

    // Normal vertex
    if (mesh->mNormals != nullptr) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
    } else {
      vector = glm::vec4(0.0f);
    }
    vertex.vn = vector;

    // Texture vertex
    if (mesh->mTextureCoords[0] != nullptr) {
      vector.x = mesh->mTextureCoords[0][i].x;
      vector.y = mesh->mTextureCoords[0][i].x;
    } else {
      vertex.vt = glm::vec4(0.0f);
    }
    vertex.vt = vector;

#ifdef RANDOM_COLORS
    float colors[] = {(std::rand() % 101) * 0.01f, std::rand() % 101 * 0.01f,
                      std::rand() % 101 * 0.01f, 1.0f};
    vector.r = colors[0];
    vector.g = colors[1];
    vector.b = colors[2];
    vertex.color = glm::vec4(vector.r, vector.g, vector.b, 1.f);
#elif COLORS
    if (mesh->mColors[0] != nullptr) {
      vector.r = mesh->mColors[0][i].r;
      vector.g = mesh->mColors[0][i].g;
      vector.b = mesh->mColors[0][i].b;
      vector.a = mesh->mColors[0][i].a;
    } else {
      vertex.color = glm::vec4(0.0f);
    }
    vertex.color = vector;
#endif  // RANDOM_COLORS

    // Tangent vector
    if (mesh->mTangents != nullptr) {
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
    } else {
      vertex.tangent = glm::vec4(0.0f);
    }
    vertex.tangent = vector;

    // Bitangets
    if (mesh->mBitangents != nullptr) {
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
    } else {
      vertex.bitangent = glm::vec4(0.0f);
    }
    vertex.bitangent = vector;

    vertices.push_back(vertex);
  }

  // Process indices
  for (std::uint32_t i = 0; i < mesh->mNumFaces; ++i) {
    const aiFace *face = &mesh->mFaces[i];
    for (std::uint32_t j = 0; j < face->mNumIndices; ++j) {
      indices.push_back(face->mIndices[j]);
    }
  }

  // !TODO Load and bind textures
  // empty textures
  std::map<std::string, Texture> textures;

  return {std::move(vertices), std::move(indices), textures};
}
