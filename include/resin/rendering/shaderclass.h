#ifndef SHADERCLASS_H
#define SHADERCLASS_H

#include <QOpenGLFunctions_3_3_Core>
#include <string>

class Shader
{
public:
    Shader(QOpenGLFunctions_3_3_Core* gl, const char* vertexShader, const char* fragmentShader);

    ~Shader();

    void Activate();
    void Delete();

    unsigned int id;

private:
    QOpenGLFunctions_3_3_Core* gl;

    std::string vertexCode;
    std::string fragmentCode;

    std::string get_file_contents(const char* filename);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};

#endif // SHADERCLASS_H