#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>

#include "../include/resin/rendering/shaderclass.h"
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

private:
    VAO* VAO1 = nullptr;
    VBO* VBO1 = nullptr;
    EBO* EBO1 = nullptr;
    Shader* shader = nullptr;

    unsigned int uniID;
};

#endif // GLWIDGET_H
