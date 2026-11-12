#include "../include/resin/rendering/shaderclass.h"

#include <iostream>
#include <fstream>
// #include <sstream>
#include <string>

std::string Shader::get_file_contents(const char* filename)
{
    // Learn more on this and make it more efficient
    // std::cout << "Tried to get content from: " << filename << std::endl;
    std::string path = std::string(SHADER_DIR) + "/" + filename;
    std::ifstream in(path, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

Shader::Shader(QOpenGLFunctions_3_3_Core* gl, const char* vertexFile, const char* fragmentFile): id(0), gl(gl)
{
    // Read vertexFile and fragmentFile and store the strings
    vertexCode = get_file_contents(vertexFile);
    fragmentCode = get_file_contents(fragmentFile);

    // Convert the shader source strings into character arrays
    // const char* vertexSource = vertexCode.c_str();
    // const char* fragmentSource = fragmentCode.c_str();

    id = CreateShader(vertexCode, fragmentCode);
}

Shader::~Shader()
{
    Delete();
}

unsigned int Shader::CompileShader( const std::string& source, unsigned int type)
{
    unsigned int id = gl->glCreateShader(type);
    const char* src = source.c_str();
    gl->glShaderSource(id, 1, &src, nullptr);
    gl->glCompileShader(id);

    // Error handling
    int result;
    gl->glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        gl->glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        gl->glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        gl->glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = gl->glCreateProgram();
    unsigned int vs =      CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs =      CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    if (vs == 0 || fs == 0)
    {
        gl->glDeleteProgram(program);
        return 0;
    }

    gl->glAttachShader(program, vs);
    gl->glAttachShader(program, fs);

    gl->glLinkProgram(program);

    int result;
    gl->glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        gl->glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

        std::string message(length, '\0');

        gl->glGetProgramInfoLog(
            program, length, nullptr, message.data()
            );

        std::cout << "Shader linking failed:\n" << message << std::endl;

        gl->glDeleteProgram(program);
        program = 0;
    }

    // gl->glValidateProgram(program);

    gl->glDeleteShader(vs);
    gl->glDeleteShader(fs);

    return program;
}

void Shader::Activate()
{
    gl->glUseProgram(id);
}
void Shader::Delete()
{
    gl->glDeleteProgram(id);
}