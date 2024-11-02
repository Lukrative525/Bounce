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
    simulation.add_ball(1, 0, 0, 0.1);
    simulation.add_ball(1, 1, 0, 0.1);
    graphicsViewer->camera.set_camera_position(0.0, -1.0, 0.0);
    graphicsViewer->camera.set_camera_target(0.0, 1.0, 0.0);
    graphicsViewer->camera.set_camera_up_direction(0.0, 0.0, 1.0);
    graphicsViewer->camera.set_far_plane(2.0);
    graphicsViewer->camera.set_near_plane(0.1);
    graphicsViewer->camera.set_height(1.0);
    graphicsViewer->camera.set_width(16.0 / 9.0);
    graphicsViewer->camera.build_projection_matrix();
    graphicsViewer->camera.build_view_matrix();

    update();
}

void MainWindow::update()
{
    graphicsViewer->update_graphics(simulation.ballCollection);
}
