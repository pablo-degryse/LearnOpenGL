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
    int dataCount;

    VertexBuffer(float* data, int dataCount, unsigned int usage);
    void bind() const;
};

struct VertexAttributeDescriptor
{
    VertexAttribute* attributes;
    int count;
    int stride;
    VertexAttributeDescriptor(VertexAttribute* attributes, int count, int stride);
};

struct IndexBuffer
{
    unsigned int id;
    unsigned int* data;
    int dataLength;

    IndexBuffer(unsigned int* data, int dataLength, unsigned int usage);
    void bind() const;
};