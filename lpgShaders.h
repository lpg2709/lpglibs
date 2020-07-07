#ifndef LPGSHADERS_H
#define LPGSHADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char *lpgLoadShaderSource(const char *path);
unsigned int lpgCreateShader(const char *shaderSourceStr, GLenum type);
unsigned int lpgCreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
void lpgDeleteShader(unsigned int shader);

#endif
