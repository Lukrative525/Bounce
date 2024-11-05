#include <QTimer>
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

    setup();
    start_timer();
}

void MainWindow::setup()
{
    framesPerSecond = 30;
    graphicsViewer->simulation.set_time_step(1.0f / framesPerSecond);
    graphicsViewer->simulation.set_gravity(Vector3D{0, 0, -1});
    graphicsViewer->simulation.add_ball(2, 0, 2);
    graphicsViewer->simulation.add_ball(8, 0, 8);
    graphicsViewer->camera.set_camera_position(0, -1, 0);
}

void MainWindow::start_timer()
{
    QTimer* timer = new QTimer(this);
    float secToMilliSeconds{1000};
    int timerInterval = (1.0f / framesPerSecond) * secToMilliSeconds;
    timer->setInterval(timerInterval);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    timer->start();
}

void MainWindow::on_timer()
{
    graphicsViewer->simulation.update();
    graphicsViewer->update_ball_positions();
}
