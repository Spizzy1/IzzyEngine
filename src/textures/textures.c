#include "../Collections/libraries.h"
#include "textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void select_texture(struct Texture* texture, int uniform){
    if(texture){
        glActiveTexture(GL_TEXTURE0 + texture->ID);
        glBindTexture(GL_TEXTURE_2D, texture->ID);
        glUniform1i(uniform, texture->ID);
    }
    else{
        printf("Expected texture, got %d", texture); 
    }
}
struct Texture* load_image(const char* path){

    printf("\n-- LOADING TEXTURE: %s --\n", path);
    //Rember evil
    struct Texture* texture = malloc(sizeof(struct Texture));
    unsigned char* bytes = stbi_load(path, &texture->width, &texture->height, &texture->bpp, 4);
    glGenTextures(1, &texture->ID);

    //Binds texture (selects it)
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    printf("setting parameters for image\n");
    //Defaults to taking closest pixel to coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Makes pixel indexing wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    printf("%d\n",glGetError());

    //Trust me.
    //Sets parameters for texture
    printf("Parsing byte array: %d to GPU\n", bytes);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    printf("Finished parsing texture to GPU\n");
    //Unselects it
    glBindTexture(GL_TEXTURE_2D, 0);
    if(bytes){
        stbi_image_free(bytes);
    }
    printf("Texture parsing cleaned up\n");
    return texture;

}