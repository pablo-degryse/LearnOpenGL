#include "Texture.h"
#include <assert.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <glad/gl.h>

Texture::Texture(const char* imageFile, unsigned int type)
    : type(type)
{
    stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(imageFile, &width, &height, &nrOfChannels, 0);
    GLenum format = GL_RGBA;
    if(nrOfChannels < 4)
        format = GL_RGB;
	assert(data != nullptr);
	glGenTextures(1, &id);
	glBindTexture(type, id);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (void*)data);
	glGenerateMipmap(type);
	stbi_image_free((void*)data);
}

void Texture::bind(unsigned int target) const
{
    glActiveTexture(target);
    glBindTexture(type, id);
}
