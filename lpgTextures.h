#ifndef LPGTEXTURES_H
#define LPGTEXTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

unsigned int lpgCreateTexture();
void lpgConfigureTextureDefoult(unsigned int texture);
unsigned int lpgTextureData(unsigned int texture, unsigned int target, const char *filePath, int internalFormat);
void lpgBindTexture(unsigned int texture, unsigned int target);
void lpgDeleteTexture(unsigned int texture);



#endif // LPGTEXTURES_H
