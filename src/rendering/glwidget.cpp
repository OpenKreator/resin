#include "../include/resin/rendering/glwidget.h"

#include <iostream>

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]()
            {
                rotation += 0.5f;

                if (rotation >= 360.0f)
                    rotation -= 360.0f;

                update();
            });

    timer->start(16);
}
GLWidget::~GLWidget()
{
    // Clean up
    makeCurrent();

    delete shader;
    delete VAO1;
    delete VBO1;
    delete EBO1;

    delete popCat;

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

    // Vertices coordinates
    GLfloat vertices[] =
        { //     COORDINATES     /        COLORS      /   TexCoord  //
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
            0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
            0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
            0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
        };

    // Indices for vertices order
    GLuint indices[] =
        {
            0, 1, 2,
            0, 2, 3,
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4
        };

    // Shader shader = (ShaderClass.cpp)
    shader = new Shader(this, "default.vert", "default.frag");

    // Vertex and buffer arrays
    VAO1 = new VAO(this);
    VBO1 = new VBO(this, vertices, sizeof(vertices));
    EBO1 = new EBO(this, indices, sizeof(indices));

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

    // Texture
    std::string path = std::string(TEXTURE_DIR) + "/" + "pop_cat.jpg";
    popCat = new Texture(this, path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    // Called every frame
    // Set every pixel in the fram buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw triangle
    // glBegin(GL_TRIANGLES);
    //     glVertex2f(0.0f, 0.707f);
    //     glVertex2f(-0.5f, -0.5f);
    //     glVertex2f(0.5f, -0.5f);
    // glEnd();

    shader->Activate();

    // 3d
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view =  glm::mat4(1.0f);
    glm::mat4 proj =  glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    view =  glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
    proj =  glm::perspective(glm::radians(45.0f), (float)(800/800), 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shader->id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shader->id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shader->id, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    glUniform1f(uniID, 0.5f);
    popCat->Bind();

    VAO1->Bind();
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}