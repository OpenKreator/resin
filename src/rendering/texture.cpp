#include "../Include/resin/rendering/texture.h"

#include <iostream>

Texture::Texture(QOpenGLFunctions_3_3_Core* gl, const char* image_path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) : id(0), gl(gl)
{
    type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image_path, &widthImg, &heightImg, &numColCh, 0);

    if (!bytes)
    {
        std::cerr << "Failed to load texture: "
                  << image_path << std::endl;

        std::cerr << "Reason: "
                  << stbi_failure_reason() << std::endl;

        return;
    }

    gl->glGenTextures(1, &id);
    gl->glActiveTexture(slot);
    gl->glBindTexture(texType, id);

    gl->glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    gl->glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    gl->glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl->glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    gl->glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Check in the future

    gl->glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
    gl->glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

Texture::~Texture()
{
    Delete();
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    unsigned int texUni = gl->glGetUniformLocation(shader.id, uniform);
    shader.Activate();
    gl->glUniform1i(texUni, 0);
}

void Texture::Bind()
{
    gl->glBindTexture(type, id);
}

void Texture::Unbind()
{
    gl->glBindTexture(type, 0);
}

void Texture::Delete()
{
    if (id != 0)
    {
        gl->glDeleteTextures(1, &id);
        id = 0;
    }
}