#include "../include/resin/gui/glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    // Clean up
    makeCurrent();

    delete shader;
    delete VAO1;
    delete VBO1;
    delete EBO1;

    doneCurrent();
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
    glClearColor(0.07, 0.13f, 0.17, 1);

    float vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    };

    unsigned int indices[] = {
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout (location=0) in vec3 aPos;"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";


    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "out vec4 FragColor;"
        "\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
        "}\n";

    // Shader shader = (ShaderClass.cpp)
    shader = new Shader(this, vertexShader, fragmentShader);

    // Vertex and buffer arrays
    VAO1 = new VAO(this);
    VBO1 = new VBO(this, vertices, sizeof(vertices));
    EBO1 = new EBO(this, indices, 9);

    VAO1->Bind();
    VBO1->Bind();
    EBO1->Bind();

    VAO1->LinkVBO(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    VAO1->Unbind();
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

    shader->Activate();

    VAO1->Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}