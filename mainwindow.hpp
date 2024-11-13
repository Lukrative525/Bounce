#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "simulation.hpp"
class GraphicsViewer;

namespace Ui
{
class MainWindowForm;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void on_timer();
    void start_timer();
    void stop_timer();
    void open_file();

private:
    void setup_timer();
    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
    QTimer* timer;
    Simulation simulation;
    double framesPerSecond;
    int subSteps;
};

#endif // MAINWINDOW_HPP
