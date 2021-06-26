#include "VertexArray.h"
#include <glad/gl.h>

VertexArray::VertexArray(unsigned int primitiveType, int nrOfElements, bool isIndexed)
    : primitiveType(primitiveType),
      nrOfElements(nrOfElements),
      isIndexed(isIndexed),
      vertexAttributeIndex(0)
{
    glGenVertexArrays(1, &id);
}

void VertexArray::RegisterVertexBufferAttributes(const VertexBuffer& vertexBuffer,
    const VertexAttributeDescriptor& vertexAttribsDesc)
{
    vertexBuffer.bind();
    for(int i = 0; i < vertexAttribsDesc.count; ++i) {
        VertexAttribute attrib = vertexAttribsDesc.attributes[i];
        glVertexAttribPointer(vertexAttributeIndex, attrib.size, GL_FLOAT, GL_FALSE, 
            vertexAttribsDesc.stride * sizeof(float), (void*)(attrib.offset * sizeof(float)));
	    glEnableVertexAttribArray(vertexAttributeIndex);
        ++vertexAttributeIndex;
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}