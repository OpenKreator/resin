#include "../include/resin/rendering/VAO.h"

VAO::VAO(QOpenGLFunctions_3_3_Core* gl) : id(0), gl(gl)
{
    gl->glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
    Delete();
}

void VAO::LinkVBO(unsigned int index, int count, unsigned int type, bool normalized, int stride, unsigned int offset)
{
    gl->glVertexAttribPointer(index, count, type, normalized ? GL_TRUE : GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    gl->glEnableVertexAttribArray(0);
}

void VAO::Bind()
{
    gl->glBindVertexArray(id);
}

void VAO::Unbind()
{
    gl->glBindVertexArray(0);
}

void VAO::Delete()
{
    if (id != 0)
    {
        gl->glDeleteVertexArrays(1, &id);
        id = 0;
    }
}