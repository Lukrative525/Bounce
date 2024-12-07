#include <QFileDialog>
#include <QJsonDocument>
#include <QKeyEvent>
#include <QTimer>
#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "physicsfunctions.hpp"
#include "ui_mainwindowform.h"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow{parent},
    mainWindowUI{new Ui::MainWindowForm},
    framesPerSecond{60},
    subSteps{10}
{
    mainWindowUI->setupUi(this);
    mainWindowUI->actionPause->setEnabled(false);
    mainWindowUI->actionStart->setEnabled(false);

    graphicsViewer = new GraphicsViewer(mainWindowUI->frame);
    mainWindowUI->frameGridLayout->addWidget(graphicsViewer);
    connect(graphicsViewer, &GraphicsViewer::request_process_mouse_click, this, &MainWindow::process_mouse_click);

    setup_timer();
    setup_menu();

    selectedBall = nullptr;
}

void MainWindow::process_mouse_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates)
{
    selectedBall = nullptr;
    Ball candidateBall{pressCoordinates.x, pressCoordinates.y, pressCoordinates.z};

    if (phys::detect_collision_with_container(candidateBall, simulation.container))
    {
        selectedBall = &simulation.container;
    }

    for (Ball& ball: simulation.ballCollection)
    {
        if (phys::detect_collision_between_balls(candidateBall, ball))
        {
            selectedBall = &ball;
            break;
        }
    }

    if (selectedBall == nullptr)
    {
        simulation.add_ball(candidateBall);
        selectedBall = &simulation.ballCollection.back();
        graphicsViewer->refresh_ball_positions(simulation.ballCollection, simulation.container);
        graphicsViewer->update();
    }

    qDebug() << selectedBall;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        selectedBall = nullptr;
        qDebug() << selectedBall;
    }
    else {
        QMainWindow::keyPressEvent(event); // Call the base class implementation for other keys.
    }
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

void MainWindow::start_timer()
{
    timer->start();
}

void MainWindow::stop_timer()
{
    timer->stop();
}

void MainWindow::open_file()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Simulation File", "", "*.sim");

    if (fileName == "")
    {
        return;
    }

    reset_simulation();

    QFile fileToOpen(fileName);
    if (fileToOpen.open(QIODevice::ReadOnly))
    {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(fileToOpen.readAll());
        if (!jsonDocument.isNull()) {
            simulation.read_from_json(jsonDocument.object());
        }
        fileToOpen.close();
    }

    graphicsViewer->initialize_camera(simulation.container);
    graphicsViewer->refresh_ball_positions(simulation.ballCollection, simulation.container);
    graphicsViewer->update();

    mainWindowUI->actionPause->setEnabled(true);
    mainWindowUI->actionStart->setEnabled(true);
}

void MainWindow::save_as_file()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Simulation File As", "", "*.sim");

    QFile fileToSave(fileName);

    if (fileToSave.open(QIODevice::WriteOnly))
    {
        QJsonObject jsonObject = simulation.write_to_json();
        QJsonDocument jsonDocument(jsonObject);
        fileToSave.write(jsonDocument.toJson());
        fileToSave.close();
    }
}

void MainWindow::setup_timer()
{
    timer = new QTimer(this);
    double secToMilliSeconds{1000};
    int timerInterval = (1.0 / framesPerSecond) * secToMilliSeconds;
    timer->setInterval(timerInterval);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()));
}

void MainWindow::setup_menu()
{
    connect(mainWindowUI->actionPause, SIGNAL(triggered()), this, SLOT(stop_timer()));
    connect(mainWindowUI->actionStart, SIGNAL(triggered()), this, SLOT(start_timer()));
    connect(mainWindowUI->actionOpen, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(mainWindowUI->actionSaveAs, SIGNAL(triggered()), this, SLOT(save_as_file()));
}

void MainWindow::reset_simulation()
{
    simulation = Simulation();
}
