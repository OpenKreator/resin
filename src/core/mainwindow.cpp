#include "../include/resin/core/mainwindow.h"
#include "../ui/ui_mainwindow.h"
#include "../include/resin/rendering/glwidget.h"

#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <iostream>
#include "DockManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_DockManager = new ads::CDockManager(this);

    // Create example content label - this can be any application specific
    // widget
    // Any qtwidget object can be set in a dockwidget
    GLWidget* gLWidget = new GLWidget(this);

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* DockWidget = m_DockManager->createDockWidget("Scene");
    DockWidget->setWidget(gLWidget);

    // Add the toggleViewAction of the dock widget to the menu to give
    // the user the possibility to show the dock widget if it has been closed
    ui->menubar->addAction(DockWidget->toggleViewAction());

    // Add the dock widget to the top dock widget area
    m_DockManager->addDockWidget(ads::TopDockWidgetArea, DockWidget);

    setWindowTitle("Resin - 3D Model Painter");

    std::cout << __cplusplus << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}