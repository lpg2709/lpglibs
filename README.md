# lpglibs

Repository for storing libs used with OpenGL.

## Libs

### lpgCamrea.h

Data to store a simple camera, function to control the camera. By default camera is sandbox.

### lpgShaders.h

Load a shader from file, create and compile shaders.
```c
/*! @brief Load shader source from file
 *  @param [const char *] path - The path of the file
 *  @return const char * - Content of the file
 */
const char *lpgLoadShaderSource(const char *path);

/*! @brief Create and compile the shader object
 *  @param [const char *] shaderSourceStr - The shader string
 *  @param [GLenum] type - Shader type
 *  @return unsigned int - Shader Id
 */
unsigned int lpgCreateShader(const char *shaderSourceStr, GLenum type);

/*! @brief Create, link and validate the program object
 *  @param [unsigned int] vertexShader - The vertex shader
 *  @param [unsigned int] fragmentShader - The fragment shader
 *  @return unsigned int - Program Id
 */
unsigned int lpgCreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

/*! @brief Delete Shader from memory
 *  @param [unsigned int] shader - Shader Id
 *  @return void
 */
void lpgDeleteShader(unsigned int shader);
```


### lpgTextures.h

Create texturs.
