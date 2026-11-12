#ifndef VAO_H
#define VAO_H

#include <QOpenGLFunctions_3_3_Core>

class VAO
{
public:
    VAO(QOpenGLFunctions_3_3_Core* gl);

    ~VAO();

    void LinkAttrib(unsigned int index, int count, unsigned int type, bool normalized, int stride, unsigned int offset);
    void Bind();
    void Unbind();
    void Delete();

    unsigned int id;

private:
    QOpenGLFunctions_3_3_Core* gl;
};

#endif // VAO_H
