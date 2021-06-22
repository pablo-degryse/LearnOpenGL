#pragma once

struct VertexAttribute
{
    int size;
    int offset;

    VertexAttribute(int size, int offset) : size(size), offset(offset) {}
};

struct VertexBuffer
{
    unsigned int id;
    float* data;
    int dataLength;
    int attributeStride;
    VertexAttribute* attributes;
    int nrOfAttributes;

    VertexBuffer(float* data, int dataLength, unsigned int usage, int attributeStride, 
        VertexAttribute* attributes, int nrOfAttributes);
    void bind() const;
};

struct IndexBuffer
{
    unsigned int id;
    unsigned int* data;
    int dataLength;

    IndexBuffer(unsigned int* data, int dataLength, unsigned int usage);
    void bind() const;
};