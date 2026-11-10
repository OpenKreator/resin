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
    glClearColor(0.5, 1, 1, 1);
}

void GLWidget::paintGL()
{
    // Set every pixel in the fram buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);       // red
        glVertex3f(0.0f, 0.707f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);       // green
        glVertex3f(-0.5f, -0.5f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);       // blue
        glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();
}