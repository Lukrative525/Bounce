#include <QFileDialog>
#include <QJsonDocument>
#include <QShortcut>
#include <QTimer>
#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "physicsfunctions.hpp"
#include "ui_mainwindowform.h"
#include "simulation.hpp"
#include "vector3d.hpp"

MainWindow::MainWindow(QWidget* parent):
    QMainWindow{parent},
    mainWindowUI{new Ui::MainWindowForm}
{
    mainWindowUI->setupUi(this);
    mainWindowUI->actionPause->setEnabled(false);
    mainWindowUI->actionPlay->setEnabled(false);

    graphicsViewer = new GraphicsViewer(mainWindowUI->frame);
    mainWindowUI->frameGridLayout->addWidget(graphicsViewer);

    simulation = new Simulation;

    setup_menu();
    setup_mouse();
    setup_shortcuts();
    setup_timer();

    on_escape_pressed();
}

MainWindow::~MainWindow()
{
    delete simulation;
}

void MainWindow::process_mouse_press(const glm::vec3& pressCoordinates)
{
    update_ball_selection(nullptr);
    mainWindowUI->centralWidget->setFocus();

    Vector3D selectionPoint{pressCoordinates.x, pressCoordinates.y, pressCoordinates.z};

    for (Ball& ball: simulation->ballCollection)
    {
        if (detect_ball_selected(selectionPoint, ball))
        {
            update_ball_selection(&ball);
            break;
        }
    }
}

void MainWindow::process_left_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates)
{
    Vector3D impartedVelocity{};
    impartedVelocity.x = inputVelocityScaleFactor * (releaseCoordinates.x - pressCoordinates.x);
    impartedVelocity.y = inputVelocityScaleFactor * (releaseCoordinates.y - pressCoordinates.y);
    impartedVelocity.z = inputVelocityScaleFactor * (releaseCoordinates.z - pressCoordinates.z);

    if (selectedBall != nullptr)
    {
        selectedBall->velocity = selectedBall->velocity + impartedVelocity;
    }
}

void MainWindow::process_right_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates)
{
    Vector3D impartedVelocity{};
    impartedVelocity.x = inputVelocityScaleFactor * (releaseCoordinates.x - pressCoordinates.x);
    impartedVelocity.y = inputVelocityScaleFactor * (releaseCoordinates.y - pressCoordinates.y);
    impartedVelocity.z = inputVelocityScaleFactor * (releaseCoordinates.z - pressCoordinates.z);

    if (selectedBall == nullptr)
    {
        Ball candidateBall{pressCoordinates.x, pressCoordinates.y, pressCoordinates.z};
        candidateBall.velocity = impartedVelocity;
        candidateBall.radius = mainWindowUI->ballRadiusDoubleSpinBox->value();
        candidateBall.elasticity = mainWindowUI->ballElasticityDoubleSpinBox->value();
        candidateBall.color.r = (mainWindowUI->ballRedSpinBox->value()) / 255.0;
        candidateBall.color.g = (mainWindowUI->ballGreenSpinBox->value()) / 255.0;
        candidateBall.color.b = (mainWindowUI->ballBlueSpinBox->value()) / 255.0;
        candidateBall.isMovable = mainWindowUI->ballMovableCheckBox->isChecked();
        phys::update_next_state_implicit_euler(simulation->timeStep, candidateBall, simulation->gravity);
        bool noCollisionDetected{true};

        for (Ball& ball: simulation->ballCollection)
        {
            if (phys::detect_collision_between_balls(candidateBall, ball))
            {
                noCollisionDetected = false;
                break;
            }
        }

        if (phys::detect_collision_with_container(candidateBall, simulation->container))
        {
            noCollisionDetected = false;
        }

        if (noCollisionDetected)
        {
            simulation->add_ball(candidateBall);
            update_ball_selection(&simulation->ballCollection.back());
            graphicsViewer->refresh_ball_positions(simulation->ballCollection, simulation->container);
            graphicsViewer->update();
        }
    }
}

bool MainWindow::detect_ball_selected(Vector3D& selectionPoint, Ball& ball)
{
    bool ballSelected = phys::calculate_distance_between(selectionPoint, ball.position) < ball.radius;

    return ballSelected;
}

void MainWindow::update_container_properties()
{
    mainWindowUI->containerXDoubleSpinBox->setValue(simulation->container.position.x);
    mainWindowUI->containerYDoubleSpinBox->setValue(simulation->container.position.y);
    mainWindowUI->containerZDoubleSpinBox->setValue(simulation->container.position.z);
    mainWindowUI->containerRadiusDoubleSpinBox->setValue(simulation->container.radius);
    mainWindowUI->containerElasticityDoubleSpinBox->setValue(simulation->container.elasticity);
}

void MainWindow::update_ball_selection(Ball* ball_address)
{
    selectedBall = ball_address;
    if (selectedBall != nullptr)
    {
        mainWindowUI->ballXDoubleSpinBox->setValue(selectedBall->position.x);
        mainWindowUI->ballYDoubleSpinBox->setValue(selectedBall->position.y);
        mainWindowUI->ballZDoubleSpinBox->setValue(selectedBall->position.z);
        mainWindowUI->ballRadiusDoubleSpinBox->setValue(selectedBall->radius);
        mainWindowUI->ballElasticityDoubleSpinBox->setValue(selectedBall->elasticity);
        mainWindowUI->ballRedSpinBox->setValue(selectedBall->color.r * 255);
        mainWindowUI->ballGreenSpinBox->setValue(selectedBall->color.g * 255);
        mainWindowUI->ballBlueSpinBox->setValue(selectedBall->color.b * 255);
        mainWindowUI->ballMovableCheckBox->setChecked(selectedBall->isMovable);
    }
}

void MainWindow::on_escape_pressed()
{
    mainWindowUI->centralWidget->setFocus();
    update_ball_selection(nullptr);
}

void MainWindow::on_spacebar_pressed()
{
    if (timer->isActive() && mainWindowUI->actionPause->isEnabled())
    {
        emit mainWindowUI->actionPause->triggered();
    }
    else if (mainWindowUI->actionPlay->isEnabled())
    {
        emit mainWindowUI->actionPlay->triggered();
    }
}

void MainWindow::reset_simulation()
{
    selectedBall = nullptr;
    simulation->reset();
    simulation->timeStep = 1.0 / (framesPerSecond * subSteps);
    simulation->set_max_number_balls(200);
    simulation->gravity.x = mainWindowUI->gravityXDoubleSpinBox->value();
    simulation->gravity.y = mainWindowUI->gravityYDoubleSpinBox->value();
    simulation->gravity.z = mainWindowUI->gravityZDoubleSpinBox->value();
    simulation->container.position.x = mainWindowUI->containerXDoubleSpinBox->value();
    simulation->container.position.y = mainWindowUI->containerYDoubleSpinBox->value();
    simulation->container.position.z = mainWindowUI->containerZDoubleSpinBox->value();
    simulation->container.radius = mainWindowUI->containerRadiusDoubleSpinBox->value();
    simulation->container.elasticity = mainWindowUI->containerElasticityDoubleSpinBox->value();
}

void MainWindow::setup_menu()
{
    connect(mainWindowUI->actionPause, &QAction::triggered, this, &MainWindow::stop_timer);
    connect(mainWindowUI->actionPlay, &QAction::triggered, this, &MainWindow::start_timer);
    connect(mainWindowUI->actionNew, &QAction::triggered, this, &MainWindow::new_file);
    connect(mainWindowUI->actionOpen, &QAction::triggered, this, &MainWindow::open_file);
    connect(mainWindowUI->actionSaveAs, &QAction::triggered, this, &MainWindow::save_as_file);
}

void MainWindow::setup_mouse()
{
    connect(graphicsViewer, &GraphicsViewer::request_process_mouse_press, this, &MainWindow::process_mouse_press);
    connect(graphicsViewer, &GraphicsViewer::request_process_left_click, this, &MainWindow::process_left_click);
    connect(graphicsViewer, &GraphicsViewer::request_process_right_click, this, &MainWindow::process_right_click);
}

void MainWindow::setup_shortcuts()
{
    QShortcut* escapeShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escapeShortcut, &QShortcut::activated, this, &MainWindow::on_escape_pressed);
    QShortcut* spacebarShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(spacebarShortcut, &QShortcut::activated, this, &MainWindow::on_spacebar_pressed);
}

void MainWindow::setup_timer()
{
    timer = new QTimer(this);
    double secToMilliSeconds{1000};
    timerInterval = (1.0 / framesPerSecond) * secToMilliSeconds;
    timer->setInterval(timerInterval);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer);
}

void MainWindow::new_file()
{
    reset_simulation();

    graphicsViewer->initialize_camera(simulation->container);
    graphicsViewer->refresh_ball_positions(simulation->ballCollection, simulation->container);
    graphicsViewer->update();

    mainWindowUI->actionPause->setEnabled(true);
    mainWindowUI->actionPlay->setEnabled(true);
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
            simulation->read_from_json(jsonDocument.object());
        }
        fileToOpen.close();
    }

    graphicsViewer->initialize_camera(simulation->container);
    graphicsViewer->refresh_ball_positions(simulation->ballCollection, simulation->container);
    graphicsViewer->update();

    mainWindowUI->actionPause->setEnabled(true);
    mainWindowUI->actionPlay->setEnabled(true);

    update_container_properties();
}

void MainWindow::save_as_file()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Simulation File As", "", "*.sim");

    QFile fileToSave(fileName);

    if (fileToSave.open(QIODevice::WriteOnly))
    {
        QJsonObject jsonObject = simulation->write_to_json();
        QJsonDocument jsonDocument(jsonObject);
        fileToSave.write(jsonDocument.toJson());
        fileToSave.close();
    }
}

void MainWindow::on_timer()
{
    for (int i{0}; i < subSteps; i++)
    {
        simulation->update();
    }

    graphicsViewer->refresh_ball_positions(simulation->ballCollection, simulation->container);
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







