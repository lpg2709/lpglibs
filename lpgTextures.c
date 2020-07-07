#include "lpgTextures.h"

unsigned int lpgCreateTexture(){
    unsigned int texture;
    glGenTextures(1, &texture);

    return texture;
}

void lpgConfigureTextureDefoult(unsigned int texture){
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int lpgTextureData(unsigned int texture, unsigned int target, const char *filePath, int internalFormat){
    int width, height,nrChannels;

    glBindTexture(target, texture);
    stbi_set_flip_vertically_on_load(1);
    unsigned char *imageData = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if(!imageData){
        printf("Erro ao carregar a imagem: %s \n", filePath);
        return -1;
    }

    glTexImage2D(target, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(target);

    stbi_image_free(imageData);

    return 0;
}

void lpgBindTexture(unsigned int texture, unsigned int target){
    glBindTexture(target, texture);
}

void lpgDeleteTexture(unsigned int texture){
    glDeleteTextures(1, &texture);
}


