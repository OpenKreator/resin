#include "../include/resin/rendering/ebo.h"

EBO::EBO(QOpenGLFunctions_3_3_Core* gl, const void* indices, unsigned int count) : id(0), gl(gl)
{
    gl->glGenBuffers(1, &id);
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    Delete();
}

void EBO::Bind()
{
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::Unbind()
{
    gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
    if (id != 0)
    {
        gl->glDeleteBuffers(1, &id);
        id = 0;
    }
}