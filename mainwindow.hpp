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
    void setup();
    void start_timer();
    Simulation simulation;

public slots:
    void on_timer();

private:
    Ui::MainWindowForm* mainWindowUI;
    GraphicsViewer* graphicsViewer;
    float framesPerSecond;
};

#endif // MAINWINDOW_HPP
