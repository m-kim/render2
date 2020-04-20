#pragma once
#include <unordered_map>

#include "Vertex.h"
#include "ModelBase.h"

class Square : public ModelBase<Square, uint16_t>
{
public:
  Square() = default;


  VkIndexType getIndexType() { return VK_INDEX_TYPE_UINT16; };

  void loadModel() {
    vertices.resize(8);
    vertices[0] = { {-0.5f, -0.5f, 0.0f}, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
    vertices[1] = { {0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f} };
    vertices[2] = { {0.5f, 0.5f, 0.0f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } };
    vertices[3] = { {-0.5f, 0.5f, 0.0f}, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } };

    vertices[4] = { {-0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } };
    vertices[5] = { {0.5f, -0.5f, -0.5f}, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } };
    vertices[6] = { {0.5f, 0.5f, -0.5f}, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } };
    vertices[7] = { {-0.5f, 0.5f, -0.5f}, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } };

    const uint16_t tmp[] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
    };

    indices.resize(12);
    for (int i = 0; i < indices.size(); i++) {
      indices[i] = tmp[i];
    }
  }
  std::vector<Vertex>& getVertices()
  {
    return vertices;
  }
  std::vector<uint16_t>& getIndices()
  {
    return indices;
  }

};