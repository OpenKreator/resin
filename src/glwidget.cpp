#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    glDeleteShader(shader);
}

// Shader logic
static unsigned int CompileShader(QOpenGLFunctions_3_3_Core* gl, const std::string& source, unsigned int type)
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

static unsigned int CreateShader(QOpenGLFunctions_3_3_Core* gl, const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = gl->glCreateProgram();
    unsigned int vs =      CompileShader(gl, vertexShader, GL_VERTEX_SHADER);
    unsigned int fs =      CompileShader(gl, fragmentShader, GL_FRAGMENT_SHADER);

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

void GLWidget::initializeGL()
{
    // Initalize open gl functions (QOpenGLFunctions_3_3_Core)
    initializeOpenGLFunctions();

    std::cout << "OpenGL Version: "
              << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLSL Version: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Clear color to cyan
    glClearColor(0, 0, 0, 0);

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    // unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = position;\n"
        "}\n";


    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location=0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "    color = vec4(0.0,0.0,1.0,1.0);\n"
        "}\n";

    // unsigned int shader = CreateShader(this, vertexShader, fragmentShader);
    shader = CreateShader(this, vertexShader, fragmentShader);
    glUseProgram(shader);
}

void GLWidget::paintGL()
{
    // Called every frame
    // Set every pixel in the fram buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle
    // glBegin(GL_TRIANGLES);
    //     glVertex2f(0.0f, 0.707f);
    //     glVertex2f(-0.5f, -0.5f);
    //     glVertex2f(0.5f, -0.5f);
    // glEnd();

    glUseProgram(shader); // Removing stops rendering the triangle
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}