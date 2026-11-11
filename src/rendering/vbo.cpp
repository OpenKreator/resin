#include "../include/resin/rendering/vbo.h"

VBO::VBO(QOpenGLFunctions_3_3_Core* gl, const void* vertices, unsigned int size) : id(0), gl(gl)
{
    gl->glGenBuffers(1, &id);
    gl->glBindBuffer(GL_ARRAY_BUFFER, id);
    gl->glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
    Delete();
}

void VBO::Bind()
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::Unbind()
{
    gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
    if (id != 0)
    {
        gl->glDeleteBuffers(1, &id);
        id = 0;
    }
}