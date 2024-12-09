#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <glm/glm.hpp>

class Ball;
class GraphicsViewer;
class PropertiesEditor;
class Simulation;
class Vector3D;

namespace Ui
{
class MainWindowForm;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void update(bool refreshCamera);

public slots:
    void process_mouse_press(const glm::vec3& pressCoordinates);
    void process_left_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates);
    void process_right_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates);

private:
    bool detect_ball_selected(Vector3D& selectionPoint, Ball& ball);
    void update_gravity_properties();
    void update_container_properties();
    void update_ball_selection(Ball* ball_address);
    void on_escape_pressed();
    void on_spacebar_pressed();
    void reset_simulation();

    void setup_menu();
    void setup_mouse();
    void setup_properties_editor();
    void setup_shortcuts();
    void setup_timer();

    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
    PropertiesEditor* propertiesEditor;
    QTimer* timer;
    Simulation* simulation;
    Ball* selectedBall{nullptr};

    double inputVelocityScaleFactor{5};
    double framesPerSecond{60};
    int subSteps{10};
    int timerInterval;

private slots:
    void new_file();
    void open_file();
    void save_as_file();

    void on_timer();
    void start_timer();
    void stop_timer();
};

#endif // MAINWINDOW_HPP
