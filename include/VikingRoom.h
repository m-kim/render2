#pragma once
#include <unordered_map>

#include "ModelBase.h" 
#include "Vertex.h"

#include <tinyobjloader/tiny_obj_loader.h>
#include <config.h>

class VikingRoom : public ModelBase<VikingRoom, uint32_t>
{
public:
  VikingRoom() = default;


  VkIndexType getIndexType() { return VK_INDEX_TYPE_UINT32; };

  void loadModel() {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;
    std::string modelFn(MODEL_PATH);
    modelFn = modelFn + "viking_room.obj";
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelFn.c_str())) {
      throw std::runtime_error(warn + err);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
      for (const auto& index : shape.mesh.indices) {
        Vertex vertex{};

        vertex.pos = {
            attrib.vertices[3 * index.vertex_index + 0],
            attrib.vertices[3 * index.vertex_index + 1],
            attrib.vertices[3 * index.vertex_index + 2]
        };

        vertex.texCoord = {
            attrib.texcoords[2 * index.texcoord_index + 0],
            1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
        };

        vertex.color = { 1.0f, 1.0f, 1.0f };

        if (uniqueVertices.count(vertex) == 0) {
          uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
          vertices.push_back(vertex);
        }

        indices.push_back(uniqueVertices[vertex]);
      }
    }
  }

  std::vector<Vertex>& getVertices()
  {
    return vertices;
  }
  std::vector<uint32_t>& getIndices()
  {
    return indices;
  }

};