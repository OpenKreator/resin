#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // Clear color to cyan
    glClearColor(0, 0, 0, 0);

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    glDrawArrays(GL_TRIANGLES, 0, 3);
}