#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED

struct Texture{
    int width;
    int height; 
    int bpp;
    unsigned ID;
};

struct Texture* load_image(struct Texture* texture, const char* path);
void select_texture(struct Texture* texture, int uniform);

#endif