#include "../include/resin/rendering/glwidget.h"

#include <iostream>

#include <../include/glm/glm.hpp>
#include <../include/glm/gtc/matrix_transform.hpp>
#include <../include/glm/gtc/type_ptr.hpp>
#include <../include/resin/rendering/camera.h>

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GLWidget::update));

    timer->start(16); // Approximately 60 FPS
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
    delete camera;

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

    // Texture
    std::string path = std::string(TEXTURE_DIR) + "/" + "pop_cat.jpg";
    popCat = new Texture(this, path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    glEnable(GL_DEPTH_TEST);

    camera = new Camera(this, 800, 800, glm::vec3(0.0f, 0.0f, 2.0f));
}

void GLWidget::paintGL()
{
    // Called every frame (?)
    // Set every pixel in the fram buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Activate();

    camera->Inputs(keys);
    camera->Matrix(45.0f, 0.1f, 100.0f, *shader, "camMatrix");

    popCat->Bind();

    VAO1->Bind();
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
    keys.insert(event->key());
}

void GLWidget::keyReleaseEvent(QKeyEvent* event)
{
    keys.remove(event->key());
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouseLook = true;

        // Hide the cursor
        setCursor(Qt::BlankCursor);

        // Prevent camera from jumping on the first click
        if (firstClick)
        {
            QCursor::setPos(mapToGlobal(rect().center()));
            firstClick = false;
        }
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouseLook = false;

        // Show the cursor again
        unsetCursor();

        // Prepare for the next click
        firstClick = true;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!mouseLook)
        return;

    // Get the center of the widget
    QPoint center = rect().center();

    // Calculate mouse offset from the center
    float mouseX = event->position().x() - center.x();
    float mouseY = event->position().y() - center.y();

    // Rotate the camera
    camera->MouseInputs(mouseX, mouseY);

    // Move cursor back to the center
    QCursor::setPos(mapToGlobal(center));

    update();
}