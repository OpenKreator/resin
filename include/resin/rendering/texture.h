#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions_3_3_Core>
#include<stb/stb_image.h>

#include "../include/resin/rendering/shaderclass.h"

class Texture
{
public:
    Texture(QOpenGLFunctions_3_3_Core* gl, const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    ~Texture();

    void texUnit(Shader& shader, const char* uniform, GLuint unit);

    void Bind();
    void Unbind();
    void Delete();

    unsigned int id;
    GLenum type;

private:
    QOpenGLFunctions_3_3_Core* gl;
};

#endif // TEXTURE_H
