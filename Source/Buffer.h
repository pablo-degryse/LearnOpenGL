#pragma once

struct VertexAttribute
{
    int size;
    int offset;

    VertexAttribute(int size, int offset) : size(size), offset(offset) {}
};

template <typename T>
struct Buffer
{
    unsigned int id;
    unsigned int type;
    T* data;
    int dataLength;
    int attributeStride;
    VertexAttribute* vertexAttributes;
    int nrOfVertexAttribuutes;

    Buffer(unsigned int type, unsigned int usage, T* data, int dataLength,
        int attributeStride, VertexAttribute* vertexAttributes, int nrOfVertexAttribuutes);
    void bind() const { glBindBuffer(type, id); }
};

template<typename T>
Buffer<T>::Buffer(unsigned int type, unsigned int usage, T* data, int dataLength,
    int attributeStride, VertexAttribute* vertexAttributes, int nrOfVertexAttribuutes)
    : type(type),
      data(data),
      dataLength(dataLength),
      attributeStride(attributeStride),
      vertexAttributes(vertexAttributes),
      nrOfVertexAttribuutes(nrOfVertexAttribuutes)
{
	glGenBuffers(1, &id);
	glBindBuffer(type, id);
	glBufferData(type, sizeof(T) * dataLength, data, usage);
}