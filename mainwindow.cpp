#include <QFileDialog>
#include <QJsonDocument>
#include <QShortcut>
#include <QTimer>
#include "graphicsviewer.hpp"
#include "mainwindow.hpp"
#include "physicsfunctions.hpp"
#include "propertieseditor.hpp"
#include "simulation.hpp"
#include "ui_mainwindowform.h"
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

    propertiesEditor = new PropertiesEditor(this);

    simulation = new Simulation;

    setup_push_buttons();
    setup_menu();
    setup_mouse();
    setup_properties_editor();
    setup_shortcuts();
    setup_timer();

    on_escape_pressed();
}

MainWindow::~MainWindow()
{
    delete simulation;
}

void MainWindow::update(bool refreshCamera)
{
    if (refreshCamera)
    {
        graphicsViewer->refresh_camera(simulation->container);
    }
    graphicsViewer->refresh_ball_positions(simulation->get_ball_collection(), simulation->container);
    graphicsViewer->update();
}

void MainWindow::process_mouse_press(const glm::vec3& pressCoordinates)
{
    update_selected_ball(nullptr);
    mainWindowUI->centralWidget->setFocus();

    Vector3D selectionPoint{pressCoordinates.x, pressCoordinates.y, pressCoordinates.z};

    for (int i{0}; i < simulation->get_ball_collection().size(); i++)
    {
        Ball& ball = simulation->get_ball(i);
        if (detect_ball_selected(selectionPoint, ball))
        {
            update_selected_ball(&ball);
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

        for (const Ball& ball: simulation->get_ball_collection())
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
            update_selected_ball(&simulation->get_ball(simulation->get_ball_collection().size() - 1));
            update(false);
        }
    }
}

bool MainWindow::detect_ball_selected(const Vector3D& selectionPoint, const Ball& ball)
{
    bool ballSelected = phys::calculate_distance_between(selectionPoint, ball.position) < ball.radius;

    return ballSelected;
}

void MainWindow::update_gravity_properties()
{
    mainWindowUI->gravityXDoubleSpinBox->setValue(simulation->gravity.x);
    mainWindowUI->gravityYDoubleSpinBox->setValue(simulation->gravity.y);
    mainWindowUI->gravityZDoubleSpinBox->setValue(simulation->gravity.z);
}

void MainWindow::update_container_properties()
{
    mainWindowUI->containerXDoubleSpinBox->setValue(simulation->container.position.x);
    mainWindowUI->containerYDoubleSpinBox->setValue(simulation->container.position.y);
    mainWindowUI->containerZDoubleSpinBox->setValue(simulation->container.position.z);
    mainWindowUI->containerRadiusDoubleSpinBox->setValue(simulation->container.radius);
    mainWindowUI->containerElasticityDoubleSpinBox->setValue(simulation->container.elasticity);
}

void MainWindow::update_selected_ball(Ball* ballAddress)
{
    selectedBall = ballAddress;
    propertiesEditor->set_selected_ball(selectedBall);
    if (selectedBall != nullptr)
    {
        mainWindowUI->deleteBallPushButton->setEnabled(true);
        mainWindowUI->deleteLinksPushButton->setEnabled(true);

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
    else
    {
        mainWindowUI->deleteBallPushButton->setEnabled(false);
        mainWindowUI->deleteLinksPushButton->setEnabled(false);
    }
}

void MainWindow::on_escape_pressed()
{
    mainWindowUI->centralWidget->setFocus();
    update_selected_ball(nullptr);
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

void MainWindow::setup_push_buttons()
{
    connect(mainWindowUI->deleteBallPushButton, &QPushButton::clicked, this, &MainWindow::delete_selected_ball);
    connect(mainWindowUI->deleteLinksPushButton, &QPushButton::clicked, this, &MainWindow::delete_links_on_selected_ball);
}

void MainWindow::setup_properties_editor()
{
    propertiesEditor->set_gravity(&simulation->gravity);
    connect(mainWindowUI->gravityXDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_gravity_x);
    connect(mainWindowUI->gravityYDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_gravity_y);
    connect(mainWindowUI->gravityZDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_gravity_z);

    propertiesEditor->set_container(&simulation->container);
    connect(mainWindowUI->containerXDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_container_x);
    connect(mainWindowUI->containerYDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_container_y);
    connect(mainWindowUI->containerZDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_container_z);
    connect(mainWindowUI->containerRadiusDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_container_radius);
    connect(mainWindowUI->containerElasticityDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_container_elasticity);

    connect(mainWindowUI->ballXDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_x);
    connect(mainWindowUI->ballYDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_y);
    connect(mainWindowUI->ballZDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_z);
    connect(mainWindowUI->ballRadiusDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_radius);
    connect(mainWindowUI->ballElasticityDoubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_elasticity);
    connect(mainWindowUI->ballRedSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_red_component);
    connect(mainWindowUI->ballGreenSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_green_component);
    connect(mainWindowUI->ballBlueSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), propertiesEditor, &PropertiesEditor::set_ball_blue_component);
    connect(mainWindowUI->ballMovableCheckBox, &QCheckBox::checkStateChanged, propertiesEditor, &PropertiesEditor::set_ball_movable);
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

void MainWindow::delete_selected_ball()
{
    simulation->remove_ball(selectedBall);
    update_selected_ball(nullptr);
    update(false);
}

void MainWindow::delete_links_on_selected_ball()
{
    simulation->remove_links_on_ball(selectedBall);
}

void MainWindow::new_file()
{
    reset_simulation();

    update(true);

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

    update(true);

    mainWindowUI->actionPause->setEnabled(true);
    mainWindowUI->actionPlay->setEnabled(true);

    update_gravity_properties();
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

    update(false);
}

void MainWindow::start_timer()
{
    timer->start();
}

void MainWindow::stop_timer()
{
    timer->stop();
}







