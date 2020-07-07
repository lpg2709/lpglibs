#include "lpgShaders.h"

const char *lpgLoadShaderSource(const char *path){
    char *shaderText = NULL;
    int fileSize = 0;

    FILE *f = fopen(path, "r");

    if(f == NULL){
        printf("Erro ao abrir o arquivo: %s", path);
        getchar();
        exit(1);
    }

    while(fgetc(f) != EOF){
        fileSize++;
    }

    if(fileSize == 1){
        printf("O Arquivo nao posui conteudo: %s", path);
        getchar();
        exit(1);
    }

    fseek(f, 0, SEEK_SET);
    shaderText = (char*) malloc(sizeof(char) * (fileSize+1));

    if(shaderText == NULL){
        printf("Nao foi possivel alocar memoria!\n");
        getchar();
        exit(1);
    }
    fread(shaderText, 1, fileSize, f);

    shaderText[fileSize] = '\0';

    fclose(f);

    return shaderText;
}

unsigned int lpgCreateShader(const char *shaderSourceStr, GLenum type){
    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &shaderSourceStr, NULL);
    glCompileShader(shaderID);

    int status;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if(!status){
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        printf("Erro ao compilar o Shader: %s\n", shaderSourceStr);
        printf("Info log: %s\n", infoLog);
        return -1;
    }

    return shaderID;

}

unsigned int lpgCreateProgram(unsigned int vertexShader, unsigned int fragmentShader){
    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    glValidateProgram(programID);

    return programID;
}

void lpgDeleteShader(unsigned int shader){
    glDeleteShader(shader);
}

