#include "../include/resin/core/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../include/resin/gui/glwidget.h"

#include <QtOpenGLWidgets/QtOpenGLWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Resin - 3D Model Painter");

    // Create OpenGL Widget
    GLWidget* gLWidget = new GLWidget(this);

    ui->verticalLayout_2->addWidget(gLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}