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

    timer = new QTimer(this);
}

void MainWindow::startup()
{
    this->show();

    framesPerSecond = 60;
    subSteps = 10;
    float elasticity{1};
    simulation.set_time_step(1.0 / framesPerSecond / subSteps);
    simulation.set_gravity(0, 0, -9.81);
    simulation.set_container(0, 0, 10, 10);
    simulation.container.set_color(0, 1);
    simulation.container.elasticity = elasticity;

    Ball ball1{2, 0, 6, 1};
    ball1.set_color(1, 0, 0, 1);
    ball1.elasticity = elasticity;
    Ball ball2{2, 0, 12, 0.5};
    ball2.set_color(0, 1, 0, 1);
    ball2.elasticity = elasticity;
    Ball ball3{-2, 0, 12, 0.75};
    ball3.set_color(0, 0, 1, 1);
    ball3.elasticity = elasticity;
    simulation.add_ball(ball1);
    simulation.add_ball(ball2);
    simulation.add_ball(ball3);

    graphicsViewer->initialize_camera(simulation.container);
    graphicsViewer->refresh_ball_positions(simulation.ballCollection, simulation.container);

    setup_timer();
}

void MainWindow::start_timer()
{
    timer->start();
}

void MainWindow::stop_timer()
{
    timer->stop();
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

void MainWindow::setup_timer()
{
    double secToMilliSeconds{1000};
    int timerInterval = (1.0 / framesPerSecond) * secToMilliSeconds;
    timer->setInterval(timerInterval);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()));
    connect(mainWindowUI->actionPause, SIGNAL(triggered()), this, SLOT(stop_timer()));
    connect(mainWindowUI->actionStart, SIGNAL(triggered()), this, SLOT(start_timer()));
}

