#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "simulation.hpp"
class GraphicsViewer;
class Ball;

namespace Ui
{
class MainWindowForm;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

public slots:
    void process_mouse_press(const glm::vec3& pressCoordinates);
    void process_mouse_click(const glm::vec3& pressCoordinates, const glm::vec3& releaseCoordinates);

private:
    void setup_timer();
    void setup_menu();
    void setup_shortcuts();
    void reset_simulation();
    bool detect_ball_selected(Vector3D& selectionPoint, Ball& ball);
    void update_ball_selection(Ball* ball_address);
    void link_container();
    void on_escape_pressed();
    void on_spacebar_pressed();

    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
    QTimer* timer;
    Simulation simulation;
    Ball* selectedBall{nullptr};
    double framesPerSecond;
    double inputVelocityScaleFactor{5};
    int subSteps;

private slots:
    void on_timer();
    void start_timer();
    void stop_timer();
    void new_file();
    void open_file();
    void save_as_file();
};

#endif // MAINWINDOW_HPP
