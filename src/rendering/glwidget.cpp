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
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

    delete lightShader;
    delete lightVAO;
    delete lightVBO;
    delete lightEBO;

    delete popCat;
    delete camera;

    doneCurrent();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0,0,w,h);

    if (camera)
    {
        camera->Resize(w,h);
    }
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
        { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            0.5f, 0.0f,  0.5f,      0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
            0.0f, 0.8f,  0.0f,      0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
            0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
            0.0f, 0.8f,  0.0f,      0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

            0.5f, 0.0f, -0.5f,      0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
            0.5f, 0.0f,  0.5f,      0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
            0.0f, 0.8f,  0.0f,      0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

            0.5f, 0.0f,  0.5f,      0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
            0.0f, 0.8f,  0.0f,      0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
        };

    // Indices for vertices order
    GLuint indices[] =
        {
            0, 1, 2, // Bottom side
            0, 2, 3, // Bottom side
            4, 6, 5, // Left side
            7, 9, 8, // Non-facing side
            10, 12, 11, // Right side
            13, 15, 14 // Facing side
        };

    GLfloat lightVertices[] =
        { //     COORDINATES     //
            -0.1f, -0.1f,  0.1f,
            -0.1f, -0.1f, -0.1f,
            0.1f, -0.1f, -0.1f,
            0.1f, -0.1f,  0.1f,
            -0.1f,  0.1f,  0.1f,
            -0.1f,  0.1f, -0.1f,
            0.1f,  0.1f, -0.1f,
            0.1f,  0.1f,  0.1f
        };

    GLuint lightIndices[] =
        {
            0, 1, 2,
            0, 2, 3,
            0, 4, 7,
            0, 7, 3,
            3, 7, 6,
            3, 6, 2,
            2, 6, 5,
            2, 5, 1,
            1, 5, 4,
            1, 4, 0,
            4, 5, 6,
            4, 6, 7
        };

    // Pyramid
    shader = new Shader(this, "default.vert", "default.frag");
    VAO1 = new VAO(this);
    VBO1 = new VBO(this, vertices, sizeof(vertices));
    EBO1 = new EBO(this, indices, sizeof(indices));
    VAO1->Bind();
    VBO1->Bind();
    EBO1->Bind();
    VAO1->LinkAttrib(0, 3, GL_FLOAT, false, 11 * sizeof(float), 0);
    VAO1->LinkAttrib(1, 3, GL_FLOAT, false, 11 * sizeof(float), (3 * sizeof(float)));
    VAO1->LinkAttrib(2, 2, GL_FLOAT, false, 11 * sizeof(float), (6 * sizeof(float)));
    VAO1->LinkAttrib(3, 3, GL_FLOAT, false, 11 * sizeof(float), (8 * sizeof(float)));
    VAO1->Unbind();
    VBO1->Unbind();
    EBO1->Unbind();

    // Light
    lightShader = new Shader(this, "light.vert", "light.frag");
    lightVAO = new VAO(this);
    lightVBO = new VBO(this, lightVertices, sizeof(lightVertices));
    lightEBO = new EBO(this, lightIndices, sizeof(lightIndices));
    lightVAO->Bind();
    lightVBO->Bind();
    lightEBO->Bind();
    lightVAO->LinkAttrib(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    lightVAO->Unbind();
    lightVBO->Unbind();
    lightEBO->Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader->Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader->id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader->id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shader->Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader->id, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shader->id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader->id, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Texture
    std::string path = std::string(TEXTURE_DIR) + "/" + "brick.png";
    popCat = new Texture(this, path.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

    glEnable(GL_DEPTH_TEST);

    camera = new Camera(this, 800, 800, glm::vec3(0.0f, 0.0f, 2.0f));
}

void GLWidget::paintGL()
{
    // Called every frame (?)
    // Set every pixel in the fram buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //camera->Inputs(keys);
    camera->UpdateMatrix(45.0f, 0.1f, 100.0f);

    shader->Activate();
    camera->Matrix(*shader, "camMatrix");
    popCat->Bind();
    VAO1->Bind();
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

    lightShader->Activate();
    camera->Matrix(*lightShader, "camMatrix");
    lightVAO->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
        setCursor(Qt::BlankCursor);
        QCursor::setPos(mapToGlobal(rect().center()));
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent*)
{
    if (!mouseLook)
        return;

    const QPoint globalCenter = mapToGlobal(rect().center());
    const QPoint delta = QCursor::pos() - globalCenter;

    if (delta.isNull())   // stale or warp-generated event
        return;

    camera->MouseInputs(delta.x(), delta.y());
    QCursor::setPos(globalCenter);
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        mouseLook = false;

        unsetCursor();
    }
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    float scroll = event->angleDelta().y() / 120.0f;

    camera->MouseScroll(scroll);

    update();
}
