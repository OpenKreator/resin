#include "../include/resin/rendering/glwidget.h"

#include <iostream>
#include<stb/stb_image.h>

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

    glDeleteTextures(1, &texture);

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

    float vertices[] =
    { //        COORDINATES      /     COLORS      /       TEXTURES        //
        -0.5f,  -0.5f,  0.0f,      1.0f, 0.0f, 0.0f,      0.0f, 0.0f,   // Lower left corner
        -0.5f,   0.5f,  0.0f,      0.0f, 1.0f, 0.0f,      0.0f, 1.0f,   // Upper left corner
         0.5f,   0.5f,  0.0f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f,   // Upper right corner
         0.5f,  -0.5f,  0.0f,      1.0f, 1.0f, 1.0f,      1.0f, 0.0f,   // Lower right corner
    };

    unsigned int indices[] = {
        0, 2, 1,
        0, 3, 2
    };

    // Shader shader = (ShaderClass.cpp)
    shader = new Shader(this, "default.vert", "default.frag");

    // Vertex and buffer arrays
    VAO1 = new VAO(this);
    VBO1 = new VBO(this, vertices, sizeof(vertices));
    EBO1 = new EBO(this, indices, 6);

    VAO1->Bind();
    VBO1->Bind();
    EBO1->Bind();

    VAO1->LinkAttrib(0, 3, GL_FLOAT, false, 8 * sizeof(float), 0);
    VAO1->LinkAttrib(1, 3, GL_FLOAT, false, 8 * sizeof(float), (3 * sizeof(float)));
    VAO1->LinkAttrib(2, 2, GL_FLOAT, false, 8 * sizeof(float), (6 * sizeof(float)));

    VAO1->Unbind();
    VBO1->Unbind();
    EBO1->Unbind();

    uniID = glGetUniformLocation(shader->id, "scale");

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    std::string path = std::string(TEXTURE_DIR) + "/" + "pop_cat.jpg";
    unsigned char* bytes = stbi_load(path.c_str(), &widthImg, &heightImg, &numColCh, 0);

    if (!bytes)
    {
        std::cerr << "Failed to load texture: "
                  << path << std::endl;

        std::cerr << "Reason: "
                  << stbi_failure_reason() << std::endl;

        return;
    }

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    unsigned int tex0uni = glGetUniformLocation(shader->id, "tex0");
    shader->Activate();
    glUniform1i(tex0uni, 0);
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

    glUniform1f(uniID, 0.5f);
    glBindTexture(GL_TEXTURE_2D, texture);

    VAO1->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}