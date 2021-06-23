#include "Buffers.h"
#include <glad/gl.h>

VertexBuffer::VertexBuffer(float* data, int dataCount, unsigned int usage,
    int attributeStride, VertexAttribute* attributes, int attributeCount)
    : data(data),
      dataCount(dataCount),
      attributeStride(attributeStride),
      attributes(attributes),
      attributeCount(attributeCount)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataCount, data, usage);
}

void VertexBuffer::bind() const 
{ 
    glBindBuffer(GL_ARRAY_BUFFER, id); 
}

IndexBuffer::IndexBuffer(unsigned int* data, int dataLength,  unsigned int usage)
{
    glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * dataLength, data, usage);
}

void IndexBuffer::bind() const 
{ 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); 
}