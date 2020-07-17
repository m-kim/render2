#pragma once
#include "BufferCreatorBase.h"

class UniformBufferCreator : public BufferCreatorBase<UniformBufferCreator>
{
public:
  UniformBufferCreator() = default;

  void create(VkDeviceSize bufferSize, VkBuffer& Buffer, VkDeviceMemory& BufferMemory)
  {
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, Buffer, BufferMemory);
  }
};