#ifndef VBO_H
#define VBO_H

#include <QOpenGLFunctions_3_3_Core>

class VBO
{
public:
    VBO(QOpenGLFunctions_3_3_Core* gl, const void* vertices, unsigned int size);

    ~VBO();

    void Bind();
    void Unbind();
    void Delete();

    unsigned int id;

private:
    QOpenGLFunctions_3_3_Core* gl;
};

#endif // VBO_H
