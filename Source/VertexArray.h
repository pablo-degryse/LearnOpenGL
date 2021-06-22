#pragma once
#include "Buffers.h"

struct VertexArray
{
    unsigned int id;
    unsigned int primitiveType;
    int nrOfElements;
    bool isIndexed;
    int vertexAttributeIndex;

    VertexArray(unsigned int primitiveType, int nrOfElements, bool isIndexed);
    void RegisterVertexAttributes(VertexAttribute* attributes, int nrOfAttributes, int stride);
    void bind() const;
};