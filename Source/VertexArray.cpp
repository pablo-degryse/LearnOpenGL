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

void VertexArray::RegisterVertexAttributes(VertexAttribute* attributes, int nrOfAttributes, int stride)
{
    for(int i = 0; i < nrOfAttributes; ++i) {
        VertexAttribute attrib = attributes[i];
        glVertexAttribPointer(vertexAttributeIndex, attrib.size, GL_FLOAT, GL_FALSE, 
            stride * sizeof(float), (void*)(attrib.offset * sizeof(float)));
	    glEnableVertexAttribArray(vertexAttributeIndex);
        ++vertexAttributeIndex;
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}