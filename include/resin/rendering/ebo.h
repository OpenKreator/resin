#ifndef EBO_H
#define EBO_H

#include <QOpenGLFunctions_3_3_Core>

class EBO
{
public:
    EBO(QOpenGLFunctions_3_3_Core* gl, const void* indices, unsigned int size);

    ~EBO();

    void Bind();
    void Unbind();
    void Delete();

    unsigned int id;

private:
    QOpenGLFunctions_3_3_Core* gl;
};

#endif // EBO_H
