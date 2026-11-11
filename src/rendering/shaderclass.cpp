#include "../include/resin/rendering/shaderclass.h"

/*
std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
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
*/

Shader::Shader(QOpenGLFunctions_3_3_Core* gl, const std::string& vertexShader, const std::string& fragmentShader): id(0), gl(gl)
{
    id = CreateShader(vertexShader, fragmentShader);
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