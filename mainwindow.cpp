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

void MainWindow::startup()
{
    framesPerSecond = 60;
    subSteps = 10;
    simulation.set_time_step(1.0 / framesPerSecond / subSteps);
    simulation.set_gravity(0, 0, -9.81);
    simulation.set_container(0, 0, 10, 10);
    simulation.container.set_color(0, 1);
    simulation.add_ball(2, 0, 6, 1);
    simulation.ballCollection[0].set_color(1, 0, 0, 1);
    simulation.add_ball(2, 0, 12, 0.5);
    simulation.ballCollection[1].set_color(0, 1, 0, 1);
    simulation.add_ball(-2, 0, 12, 0.75);
    simulation.ballCollection[2].set_color(0, 0, 1, 1);
    graphicsViewer->initialize_camera(simulation.container);
    graphicsViewer->refresh_ball_positions(simulation.ballCollection, simulation.container);
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
    for (int i{0}; i < subSteps; i++)
    {
        simulation.update();
    }

    graphicsViewer->refresh_ball_positions(simulation.ballCollection, simulation.container);
    graphicsViewer->update();
}
