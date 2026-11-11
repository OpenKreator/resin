#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QObject>

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
    unsigned int vao;
    unsigned int buffer;
    unsigned int shader;
};

#endif // GLWIDGET_H
