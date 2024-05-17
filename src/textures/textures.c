#include "../Collections/libraries.h"
#include "textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void select_texture(struct Texture* texture, int uniform){
    struct Logger* loader = malloc(sizeof(struct Logger));
    Logger(loader, "Texture Loader");
    if(texture){
        glActiveTexture(GL_TEXTURE0 + texture->ID);
        glBindTexture(GL_TEXTURE_2D, texture->ID);
        glUniform1i(uniform, texture->ID);
    }
    else{
        cwlog(loader, LOGGER_ERROR, "Expected texture, got %d", texture); 
    }
    free(loader);
}
struct Texture* load_image(struct Texture* texture, const char* path){

    struct Logger* texLogger = malloc(sizeof(struct Logger));
    Logger(texLogger, path);
    printf("\n-- LOADING TEXTURE: %s --\n", path);
    //Rember evil
    unsigned char* bytes = stbi_load(path, &texture->width, &texture->height, &texture->bpp, 4);
    cwlog(texLogger, LOGGER_INFO, "Loaded image");
    glGenTextures(1, &texture->ID);

    cwlog(texLogger, LOGGER_INFO, "Generated textures");
    //Binds texture (selects it)
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    cwlog(texLogger, LOGGER_INFO, "setting parameters for image");
    //Defaults to taking closest pixel to coordinate
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Makes pixel indexing wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    cwlog(texLogger,LOGGER_WARN, "%d",glGetError());

    //Trust me.
    //Sets parameters for texture
    cwlog(texLogger, LOGGER_INFO, "Parsing byte array: %d to GPU", bytes);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    cwlog(texLogger, LOGGER_SETUP, "Finished parsing texture to GPU");
    //Unselects it
    glBindTexture(GL_TEXTURE_2D, 0);
    if(bytes){
        stbi_image_free(bytes);
    }
    cwlog(texLogger, LOGGER_SETUP, "Texture parsing cleaned up");
    free(texLogger);
    return texture;

}
