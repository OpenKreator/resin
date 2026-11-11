#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include<iostream>
#include <QOpenGLFunctions_3_3_Core>
#include <string>

class Shader
{
public:
    Shader(QOpenGLFunctions_3_3_Core* gl, const std::string& vertexShader, const std::string& fragmentShader);

    ~Shader();

    void Activate();
    void Delete();

private:
    unsigned int id;
    QOpenGLFunctions_3_3_Core* gl;

    unsigned int CompileShader(const std::string& source, unsigned int type);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};

#endif // SHADERCLASS_H