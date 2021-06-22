#pragma once

struct Texture
{
    unsigned int id;
    unsigned int type;
    int width;
    int height;
    int nrOfChannels;

    Texture(const char* imageFile, unsigned int type);
    void bind(unsigned int target) const;
};