#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>
#include <QTimer>
#include <QSet>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QWheelEvent>

#include "../include/resin/rendering/shaderclass.h"
#include "../include/resin/rendering/texture.h"
#include "../include/resin/rendering/camera.h"
#include "../include/resin/rendering/vbo.h"
#include "../include/resin/rendering/ebo.h"
#include "../include/resin/rendering/vao.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    GLWidget(QWidget* parent = nullptr);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    // Event voids
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    VAO* VAO1 = nullptr;
    VBO* VBO1 = nullptr;
    EBO* EBO1 = nullptr;
    Shader* shader = nullptr;

    Texture* popCat = nullptr;

    unsigned int texture;

    QTimer* timer;
    float rotation = 0.0f;

    Camera* camera = nullptr;

    QSet<int> keys;

    bool mouseLook = false;
    QPoint lastMousePos;
    void CenterCursor();
    bool ignoreNextMouseMove = false;
    bool ignoreWarpEvent = false;
};

#endif // GLWIDGET_H
