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
}

void MainWindow::setup()
{
    framesPerSecond = 30;
    simulation.set_time_step(1.0 / framesPerSecond);
    simulation.set_gravity(Vector3D{0, 0, -1});
    simulation.add_ball(2, 0, 2, 1);
    simulation.add_ball(8, 0, 8, 0.5);
    graphicsViewer->camera.set_camera_position(0, -1, 0);
    graphicsViewer->refresh_ball_positions(simulation.ballCollection);
    start_timer();
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
    simulation.update();
    graphicsViewer->refresh_ball_positions(simulation.ballCollection);
    graphicsViewer->update();
}
