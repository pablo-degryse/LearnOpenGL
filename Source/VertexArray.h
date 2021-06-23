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
    void RegisterVertexBufferAttributes(const VertexBuffer& vertexBuffer);
    void bind() const;
};