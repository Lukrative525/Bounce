#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindowform.h"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow{parent},
    mainWindowUI{new Ui::MainWindowForm}
{
    mainWindowUI->setupUi(this);
    graphicsViewer = new GraphicsViewer(mainWindowUI->frame);
    mainWindowUI->frameGridLayout->addWidget(graphicsViewer);

    simulation.add_ball();
    simulation.add_ball(10, 10, 0, 0.1);

    graphicsViewer->camera.nearPlane = -1.0;
    graphicsViewer->camera.farPlane = 1.0;
    graphicsViewer->camera.center_camera(mainWindowUI->frame->frameSize(), 0, 0, 10, 10);

    update();
}

void MainWindow::update()
{
    graphicsViewer->update_object_positions(simulation.ballCollection);
}
