#include "mesh_loader.h"

std::vector<Mesh> MeshLoader::LoadFromFile(const std::string &file_path) {
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

  return std::move(meshes_);
}

void MeshLoader::ProcessNode(const aiNode *node, const aiScene *scene) {
  for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
    meshes_.push_back(LoadMesh(scene->mMeshes[node->mMeshes[i]]));
  }

  for (uint32_t i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}

Mesh MeshLoader::LoadMesh(const aiMesh *mesh) {
  std::vector<Vertex> vertices;
  std::vector<std::uint32_t> indices;

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

    if (mesh->mColors[0] != nullptr) {
      vector.r = mesh->mColors[0][i].r;
      vector.g = mesh->mColors[0][i].g;
      vector.b = mesh->mColors[0][i].b;
      vector.a = mesh->mColors[0][i].a;
    } else {
      vertex.color = glm::vec4(0.0f);
    }
    vertex.color = vector;

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
  std::map<std::string, Texture> textures;

  return {std::move(vertices), std::move(indices), textures};
}
