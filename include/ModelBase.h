#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Vertex.h"

// OBJ representation of a vertex
struct VertexObj
{
  glm::vec3 pos;
  glm::vec3 nrm;
  glm::vec3 color;
  glm::vec2 texCoord;
};

template <class T, class IND_TYPE = uint16_t>
class ModelBase
{
public:
  ModelBase() = default;

  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;
  std::vector<Vertex> vertices;

  std::vector<IND_TYPE> indices;

  constexpr std::string_view textureName() {
    return static_cast<T*>(this)->textureName();
  }

  void loadModel() {
    static_cast<T*>(this)->loadModel();
  }

  VkIndexType getIndexType()
  {
    return static_cast<T*>(this)->getIndexType();
  }

  auto &getVertices()
  {
    return static_cast<T*>(this)->getVertices();
  }

  auto getIndices()
  {
    return static_cast<T*>(this)->getIndices();
  }

};
