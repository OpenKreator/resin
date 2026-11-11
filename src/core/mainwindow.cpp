#include "../include/resin/core/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../include/resin/gui/glwidget.h"

#include <QtOpenGLWidgets/QtOpenGLWidgets>

#include <iostream>
#include <fstream>
// #include <sstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Resin - 3D Model Painter");

    // Create OpenGL Widget
    GLWidget* gLWidget = new GLWidget(this);

    /*
    std::string path = std::string(SHADER_DIR) + "/vertex.txt";
    std::ifstream file(path);

    if (!file.is_open()){
        std::cout << "ERROR: Could not open vertex.txt!" << std::endl;
    }
    else {
        std::string line;

        while (std::getline(file, line)){
            std::cout << line << std::endl;
        }
    }
    */

    ui->verticalLayout_2->addWidget(gLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}