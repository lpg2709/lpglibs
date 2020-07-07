#ifdef LPG_CAMERA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI_DIV_180 (0.017453292519943296)
#define degreeToRad(x) ((x)*PI_DIV_180)

typedef float vec3[3];

typedef struct camera_str Camera;

enum camera_moves{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


/************************************************
 * Auxiliar math function for Camera Operations *
 ************************************************/

void addVec3(vec3 res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    res[0] = aX + bX;
    res[1] = aY + bY;
    res[2] = aZ + bZ;
}

void scaleVec3(lpgM3Dvec3f m, float x){
    m[0] = m[0] * x;
    m[1] = m[1] * x;
    m[2] = m[2] * x;
}

void scaleVec3v(lpgM3Dvec3f r, lpgM3Dvec3f m,float x){
    r[0] = m[0] * x;
    r[1] = m[1] * x;
    r[2] = m[2] * x;
}

void addVec3v(vec3 res, vec3 a, vec3 b){
    addVec3(res, a[0], a[1], a[2], b[0], b[1], b[2]);
}

void subtractVec3(vec3 res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    addVec3(res, aX, aY, aZ, -bX, -bY, -bZ);
}

void subtractVec3v(vec3 res, vec3 a, vec3 b){
    subtractVec3(res, a[0], a[1], a[2], b[0], b[1], b[2]);
}

void crossProduct3(vec3 res, float aX, float aY, float aZ, float bX, float bY, float bZ){
    res[0] = aY*bZ - bY*aZ;
    res[1] =-aX*bZ + bX*aZ;
    res[2] = aX*bY - bX*aY;
}

void crossProduct3v(vec3 m, vec3 a, vec3 b){
    crossProduct3(m, a[0], a[1], a[2], b[0], b[1], b[2]);
}

void sizeVec3(float x, float y, float z, float *tam){
    *tam = sqrt((x*x) + (y*y) + (z*z));
}

void sizeVec3v(vec3 vetor, float *tam){
    sizeVec3(vetor[0], vetor[1], vetor[2], tam);
}

void normalizeVec3(vec3 vetor){
    float tam;
    sizeVec3v(vetor, &tam);
    if(tam == 0){
        tam = 1;
    }
    vetor[0] = vetor[0] / tam;
    vetor[1] = vetor[1] / tam;
    vetor[2] = vetor[2] / tam;
}

/**********
 * CAMERA *
 **********/

struct camera_str{
    vec3 position;
    vec3 target;
    vec3 direction;
    vec3 right;
    vec3 up;
    vec3 upWord;


    float fov;
    float sensitivity;
    float velocity;

    float yaw;
    float pitch;
};

void updateVectors(Camera *camera){

    /* Direction vector of the camera */
    vec3 tempDir;
    tempDir[0] = cos(degreeToRad(camera->yaw)) * cos(degreeToRad(camera->pitch));
    tempDir[1] = sin(degreeToRad(camera->pitch));
    tempDir[2] = sin(degreeToRad(camera->yaw)) * cos(degreeToRad(camera->pitch));
    normalizeVec3(tempDir);

    camera->direction[0] = tempDir[0];
    camera->direction[1] = tempDir[1];
    camera->direction[2] = tempDir[2];

    /* Target view of the camera*/
    addVec3v(camera->target, camera->position, camera->direction);

    /* Right vector of the camera */
    vec3 tempRight;
    crossProduct3v(tempRight, camera->direction, camera->upWord);
    normalizeVec3(tempRight);

    camera->right[0] = tempRight[0];
    camera->right[1] = tempRight[1];
    camera->right[2] = tempRight[2];

    /* Up vector of the camera */
    vec3 tempUp;
    crossProduct3v(tempUp, camera->direction ,camera->right);
    normalizeVec3(tempUp);

    camera->up[0] = tempUp[0];
    camera->up[1] = tempUp[1];
    camera->up[2] = tempUp[2];
}

void processKeyboard(Camera *camera, camera_moves moves, float deltaTime){
    float velocity = camera->velocity * deltaTime;
    vec3 res;
    if(moves == FORWARD){
        scaleVec3v(res, camera->direction, velocity);
        addVec3v(camera->position, camera->position, res);
    }
    if(moves == BACKWARD){
        scaleVec3v(res, camera->direction, velocity);
        subtractVec3v(camera->position, camera->position, res);
    }
    if(moves == RIGHT){
        scaleVec3v(res, camera->right, velocity);
        addVec3v(camera->position, camera->position, res);
    }
    if(moves == LEFT){
        scaleVec3v(res, camera->right, velocity);
        subtractVec3v(camera->position, camera->position, res);
    }
    addVec3v(camera->target, camera->position, camera->direction);
}

void ProcessMouseMovement(Camera *camera, double xOffset, double yOffset, unsigned char constrainPitch){
    xOffset *= camera->sensitivity;
    yOffset *= camera->sensitivity;

    camera->yaw += xOffset;
    camera->pitch += yOffset;

    if(!constrainPitch){
        if(camera->pitch > 89.9f)
            camera->pitch = 89.9f;
        if(camera->pitch < -89.9f )
            camera->pitch = -89.9f;
    }

    updateVectors(camera);
}

void ProcessMouseScroll(Camera *camera, float yOffset){
    camera->fov -= (float)yOffset;

    if(camera->fov < 1.0f)
        camera->fov = 1.0f;
    if(camera->fov > 45.0f)
        camera->fov = 45.0f;
}

void createCamera(Camera *camera){

    /* Position of the camera */
    camera->position[0] = camera->position[1] = 0.0f;
    camera->position[2] = 3.0f;

    /* Up word direction */
    camera->upWord[0] = camera->upWord[2] = 0.0f;
    camera->upWord[1] = 1.0f;

    camera->fov = 45.0f;
    camera->sensitivity = 0.03f;
    camera->velocity = 3.0f;

    camera->yaw = -90.0f;
    camera->pitch = 0.0f;

    updateVectors(camera);

}

#endif
