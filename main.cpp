#include <QApplication>
#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "ui_mainwindowform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    window.simulation.add_ball();
    window.simulation.add_ball(10, 0, 10, 0.1);

    window.graphicsViewer->camera.nearPlane = 0.0;
    window.graphicsViewer->camera.farPlane = 1.0;
    window.graphicsViewer->camera.center_camera(window.mainWindowUI->frame->frameSize(), -2.0, -2.0, 12.0, 12.0);
    window.graphicsViewer->camera.set_camera_target(0.0, 1.0, 0.0);
    window.graphicsViewer->camera.set_camera_up_direction(0.0, 0.0, 1.0);

    window.update();
    return app.exec();
}
