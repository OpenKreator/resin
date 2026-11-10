#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

#include <QtOpenGLWidgets/QtOpenGLWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("QT Morning Adventures");

    // Create OpenGL Widget
    GLWidget* gLWidget = new GLWidget(this);

    ui->verticalLayout_2->addWidget(gLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
