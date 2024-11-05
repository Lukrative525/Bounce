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
}

void MainWindow::testFunction()
{
    // test code here
    graphicsViewer->simulation.add_ball(2, 0, 2);
    graphicsViewer->simulation.add_ball(8, 0, 8);
    graphicsViewer->update_ball_positions();
    graphicsViewer->camera.set_camera_position(0, -1, 0);
}
